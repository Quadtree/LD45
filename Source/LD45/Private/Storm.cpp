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
				StormLevel = FMath::Clamp(StormLevel + deltaTime * MaxStormLevel / 30.f, 0.f, MaxStormLevel);
			}
			else
			{
				StormLevelRising = false;
			}
		}
		else
		{
			StormLevel = FMath::Clamp(StormLevel - deltaTime * MaxStormLevel / 30.f, 0.f, MaxStormLevel);
		}
	}

	if (FMath::FRand() < StormOverallPower * deltaTime)
	{
		StartStorm(StormOverallPower * 5);
	}

	RainParticleSystem->SetFloatParameter("StormLevel", StormLevel);

	for (TActorIterator<ALD45Character> i(GetWorld()); i; ++i)
	{
		RainParticleSystem->SetWorldLocation(i->GetActorLocation() + StormVector * -1000);
		UE_LOG(LogTemp, Display, TEXT("Loc set to %s"), *(i->GetActorLocation() + StormVector * -1000).ToString());
	}
}