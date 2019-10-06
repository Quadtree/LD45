#include "FlammableComponent.h"
#include "FlammableComponent.ac.h"

extends(UActorComponent)

im(AActor)

prop(float Temperature)
prop(float Mass)
prop(float DamageRate)

classMods(meta=(BlueprintSpawnableComponent))

fun::UFlammableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	Temperature = 23;
	DamageRate = 1.5f;
}

float fun::GetHeatProduced()
{
	if (Cast<AConstructible>(GetOwner())) return 50;
	if (Cast<ATree>(GetOwner())) return 50;
	if (Cast<AStick>(GetOwner())) return 7;
	if (Cast<ABush>(GetOwner())) return 10;
	if (Cast<ALD45Character>(GetOwner())) return 25;
	return 5;
}

float fun::GetMass()
{
	if (Cast<AConstructible>(GetOwner())) return 5;
	if (Cast<ATree>(GetOwner())) return 50;
	if (Cast<AStick>(GetOwner())) return 3;
	if (Cast<ABush>(GetOwner())) return 10;
	if (Cast<ALD45Character>(GetOwner())) return 25;
	return 5;
}

/// Adds some heat, roughly in joules...
void fun::AddHeat(float roughJoules, float max)
{
	//checkf(GetMass() > 0, TEXT("%s cannot have zero mass"), *GetOwner()->GetName());

	Temperature = FMath::Min(Temperature + roughJoules / GetMass(), max);
}

/*float fu n::GetMass()
{
	float mass = 0;

	for (auto prim : GetOwner()->GetComponentsByClass(UPrimitiveComponent::StaticClass()))
	{
		if (auto prim2 = Cast<UPrimitiveComponent>(prim))
		{
			mass += prim2->GetMass();
		}
	}

	return mass;
}*/

void fun::TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(deltaTime, TickType, ThisTickFunction);

	bool isOnFire = false;

	if (Temperature > 200)
	{
		//UE_LOG(LogTemp, Display, TEXT("FIRE"));

		// WE'RE ON FIRE
		isOnFire = true;

		GetOwner()->TakeDamage(DamageRate * deltaTime, FDamageEvent(), nullptr, nullptr);

		if (Temperature < 400) Temperature += 20 * deltaTime;

		TArray<FOverlapResult> res;
		if (GetWorld()->OverlapMultiByObjectType(res, GetOwner()->GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams::AllObjects, FCollisionShape::MakeSphere(700)))
		{
			for (auto a : res)
			{
				if (!a.Actor.IsValid()) continue;
				if (a.Actor.Get() == GetOwner()) continue;
				if (auto comp = a.Actor->FindComponentByClass<UFlammableComponent>())
				{
					float dist = FMath::Max(FVector::Dist(a.Actor->GetActorLocation(), GetOwner()->GetActorLocation()), 1.f);
					comp->AddHeat(Temperature / dist * deltaTime * GetHeatProduced(), Temperature);
				}
			}
		}
	}

	Temperature += (23 - Temperature) * deltaTime * 0.04f;

	for (auto a : GetOwner()->GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		if (auto ps = Cast<UParticleSystemComponent>(a))
		{
			//ps->SetEmitterEnable("Particle Emitter", isOnFire);
			if (isOnFire && ps->bSuppressSpawning)
			{
				ps->bSuppressSpawning = false;
				ps->Activate();
				ps->ActivateSystem();
			}
			
			if (!isOnFire && !ps->bSuppressSpawning)
			{
				ps->bSuppressSpawning = true;
			}
		}
	}
}