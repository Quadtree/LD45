#include "Terrain.h"
#include "Terrain.ac.h"

extends(AActor)

prop(UStaticMesh* TerrainCube)
prop(int32 TileWidth)
prop(int32 TileHeight)

void fun::BeginPlay()
{
	for (int32 x = 0; x < TileWidth; ++x)
	{
		for (int32 y = 0; y < TileHeight; ++y)
		{

		}
	}
}