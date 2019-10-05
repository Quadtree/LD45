#include "Terrain.h"
#include "Terrain.ac.h"

extends(AActor)

prop(UInstancedStaticMeshComponent* TerrainCubes)
prop(int32 TileWidth)
prop(int32 TileHeight)

fun::ATerrain()
{
	TerrainCubes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Cubes");
	RootComponent = TerrainCubes;
}

void fun::BeginPlay()
{
	for (int32 x = 0; x < TileWidth; ++x)
	{
		for (int32 y = 0; y < TileHeight; ++y)
		{
			FTransform trans;

			trans.SetComponents(
				FQuat::Identity,
				FVector(x * 100, y * 100, 0),
				FVector(1, 1, 50)
			);

			TerrainCubes->AddInstance(trans);
		}
	}
}