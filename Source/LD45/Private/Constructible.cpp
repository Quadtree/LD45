#include "Constructible.h"
#include "Constructible.ac.h"

extends(AActor)

prop(float WoodCost)

prop(UStaticMeshComponent* StaticMesh)
prop(USceneComponent* SceneComp)
prop(float Health)

blueprintEvent(BecomeSolid);

fun::AConstructible()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SceneComp = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComp;
	StaticMesh->AttachToComponent(SceneComp, FAttachmentTransformRules::KeepRelativeTransform);
}

mods(bare) void fun::SetForConstructionAt(AActor* constructor, const FHitResult& res)
{
	if (res.ImpactNormal.Z > 0.5f)
	{
		// this is a wall
		FRotator rot = res.ImpactNormal.Rotation();
		
		FVector delta = res.Location - constructor->GetActorLocation();

		float yaw = delta.Rotation().Yaw;
		rot.Roll = -yaw;

		SetActorRotation(rot);
		SetActorLocation(res.Location);
	}
	else
	{
		// this is a ceiling
		FRotator rot = res.ImpactNormal.Rotation();

		SetActorRotation(rot);
		SetActorLocation(res.Location);
	}
}

void fun::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void fun::PlaceConstructible()
{
	if (GetActorLocation().Z > 0)
	{
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BecomeSolid();
	}
}

float fun::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0) Destroy();

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}