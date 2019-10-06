#include "Tree.h"
#include "Tree.ac.h"

extends(AActor)

prop(UStaticMeshComponent* StaticMesh)
prop(float WoodLeft)

fun::ATree()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
}

mods(bare) TMap<EResourceType, float> fun::Harvest(float harvestSpeed)
{
	float ret = FMath::Min(WoodLeft, harvestSpeed);

	if (WoodLeft <= 0.01f) Destroy();

	TMap<EResourceType, float> ret2;
	ret2.Add(EResourceType::RT_Wood, ret);

	WoodLeft -= ret;

	return ret2;
}

float fun::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	WoodLeft -= DamageAmount;

	if (WoodLeft <= 0) Destroy();

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}