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

	return ret2;
}