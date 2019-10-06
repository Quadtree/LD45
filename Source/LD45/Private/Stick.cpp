#include "Stick.h"
#include "Stick.ac.h"

extends(AActor)

prop(UStaticMeshComponent* StaticMesh)
prop(float Health)

fun::AStick()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
}

float fun::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0) Destroy();

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}