#include "FlammableComponent.h"
#include "FlammableComponent.ac.h"

extends(UActorComponent)

im(AActor)

prop(float Temperature)

fun::UFlammableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
	Temperature = 23;
}

/// Adds some heat, roughly in joules...
void fun::AddHeat(float roughJoules)
{
	Temperature += roughJoules / GetMass();
}

float fun::GetMass()
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
}

void fun::TickComponent(float deltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(deltaTime, TickType, ThisTickFunction);

	if (Temperature > 45)
	{
		TArray<FOverlapResult> res;
		if (GetWorld()->OverlapMultiByChannel(res, GetOwner()->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(700)))
		{
			for (auto a : res)
			{
				if (!a.Actor.IsValid()) continue;
				if (a.Actor.Get() == GetOwner()) continue;
				if (auto comp = a.Actor->FindComponentByClass<UFlammableComponent>())
				{
					float dist = FVector::Dist(a.Actor->GetActorLocation(), GetOwner()->GetActorLocation());
					comp->AddHeat(Temperature / dist * deltaTime);
				}
			}
		}
	}
}