#include "Storm.h"
#include "Storm.ac.h"

extends(AActor)

prop(float StormLevel)
prop(float MaxStormLevel)
prop(float StormOverallPower)
prop(bool StormLevelRising)
prop(UParticleSystemComponent* RainParticleSystem)
prop(USceneComponent* SceneComp)
prop(FVector StormVector)

fun::AStorm()
{
	RainParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("RainParticleSystem");
	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComp");
	RootComponent = SceneComp;
	RainParticleSystem->AttachToComponent(SceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	PrimaryActorTick.bCanEverTick = true;
}

void fun::StartStorm(float maxLevel)
{
	UE_LOG(LogTemp, Display, TEXT("Storm starting at power %s"), *FString::SanitizeFloat(maxLevel));

	MaxStormLevel = maxLevel;
	StormLevelRising = true;
}

void fun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (MaxStormLevel > 0.1f)
	{
		if (StormLevelRising)
		{
			if (StormLevel < MaxStormLevel)
			{
				StormLevel = FMath::Clamp(StormLevel + deltaTime * MaxStormLevel / 7.f, 0.f, MaxStormLevel);
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Storm has reached max power"));
				StormLevelRising = false;
			}
		}
		else
		{
			StormLevel = FMath::Clamp(StormLevel - deltaTime * MaxStormLevel / 4.f, 0.f, MaxStormLevel);
		}
	}

	if (FMath::FRand() < StormOverallPower * deltaTime * 0.3f)
	{
		StartStorm(StormOverallPower * 5);
	}

	RainParticleSystem->SetFloatParameter("StormLevel", StormLevel);

	if (StormLevel > 0.01f)
	{
		RainParticleSystem->ActivateSystem();
	}

	for (TActorIterator<ALD45Character> i(GetWorld()); i; ++i)
	{
		RainParticleSystem->SetWorldLocation(i->GetActorLocation() + StormVector * -2000);
		RainParticleSystem->SetWorldRotation(StormVector.Rotation());

		PotentiallyChill(*i, deltaTime);
		//UE_LOG(LogTemp, Display, TEXT("Loc set to %s"), *(i->GetActorLocation() + StormVector * -1000).ToString());

		// even if the PC is out of LOS, still chill them a bit
		i->FindComponentByClass<UFlammableComponent>()->SetTemperature(i->FindComponentByClass<UFlammableComponent>()->GetTemperature() - 0.5f * deltaTime * StormLevel);
	}

	if (StormOverallPower > 0.2f && true)
	{
		if (FMath::FRand() < StormOverallPower * deltaTime * 0.3f)
		{
			WindShear();
		}
	}

	// currently it takes 15 minutes for the storm to pass each level
	StormOverallPower += deltaTime / 60 / 15;
}

void fun::PotentiallyChill(AActor* actor, float deltaTime)
{
	if (auto tempComp = actor->FindComponentByClass<UFlammableComponent>())
	{
		FHitResult res;
		FCollisionQueryParams params;
		FCollisionObjectQueryParams op;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(actor);
		if (!GetWorld()->LineTraceTestByChannel(actor->GetActorLocation() + StormVector * -2000, actor->GetActorLocation(), ECollisionChannel::ECC_Visibility, params))
		{
			tempComp->SetTemperature(tempComp->GetTemperature() - 3 * deltaTime * StormLevel);
		}
	}
}

void fun::WindShear()
{
	StormVector.X = FMath::FRandRange(-1, 1);
	StormVector.Y = FMath::FRandRange(-1, 1);
	StormVector.Z = FMath::FRandRange(-1, 0);
	StormVector = StormVector.GetSafeNormal();

	UE_LOG(LogTemp, Display, TEXT("Storm has sheared to %s"), *StormVector.ToString());
}