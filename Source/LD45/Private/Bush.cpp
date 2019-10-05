#include "Bush.h"
#include "Bush.ac.h"

extends(AActor)

prop(UStaticMeshComponent* StaticMesh)
prop(float MaxFood)
prop(float FoodRegenRate)
prop(float FoodLeft)
prop(EResourceType BerryType)

blueprintEvent(BerryColorChanged);
blueprintEvent(ConsiderBerryVisibility);

fun::ABush()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
}

mods(bare) TMap<EResourceType, float> fun::Harvest(float harvestSpeed)
{
	float ret = FMath::Min(FoodLeft, harvestSpeed);

	TMap<EResourceType, float> ret2;
	ret2.Add(BerryType, ret);

	FoodLeft -= ret;

	ConsiderBerryVisibility();

	return ret2;
}

void fun::BeginPlay()
{
	Super::BeginPlay();

	FoodLeft = MaxFood;
}

void fun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	FoodLeft += FMath::Min(MaxFood, FoodRegenRate * deltaTime);

	if (FoodLeft >= MaxFood)
	{
		ConsiderBerryVisibility();
	}
}