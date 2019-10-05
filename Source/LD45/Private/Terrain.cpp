#include "Terrain.h"
#include "Terrain.ac.h"

extends(AActor)

prop(UInstancedStaticMeshComponent* TerrainCubes)
prop(int32 TileWidth)
prop(int32 TileHeight)

prop(bare private TArray<TArray<float>> HeightMap)

fun::ATerrain()
{
	TerrainCubes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Cubes");
	RootComponent = TerrainCubes;
}

void fun::BeginPlay()
{
	for (int32 x = 0; x < TileWidth; ++x)
	{
		HeightMap.Add(TArray<float>());
		for (int32 y = 0; y < TileHeight; ++y)
		{
			HeightMap[x].Add(0);
		}
	}

	for (int32 squareSize = TileWidth - 1; squareSize > 1; squareSize /= 2)
	{
		for (int32 x = 0; x < TileWidth; x += squareSize)
		{
			for (int32 y = 0; y < TileHeight; y += squareSize)
			{
				SquareStep(x, y, x + squareSize, y + squareSize);
			}
		}
		for (int32 x = 0; x < TileWidth; x += squareSize)
		{
			for (int32 y = 0; y < TileHeight; y += squareSize)
			{
				DiamondStep(x - squareSize / 2, y,					x + squareSize, y + squareSize);
				DiamondStep(x + squareSize / 2, y,					x + squareSize, y + squareSize);
				DiamondStep(x,					y - squareSize / 2, x + squareSize, y + squareSize);
				DiamondStep(x,					y + squareSize / 2, x + squareSize, y + squareSize);
			}
		}
	}

	for (int32 x = 0; x < TileWidth; ++x)
	{
		for (int32 y = 0; y < TileHeight; ++y)
		{
			FTransform trans;

			trans.SetComponents(
				FQuat::Identity,
				FVector(x * 100, y * 100, GetTileHeightAt(x,y)),
				FVector(1, 1, 50)
			);

			TerrainCubes->AddInstance(trans);
		}
	}
}

void fun::SetTileHeightAt(int32 x, int32 y, float height)
{
	if (x < 0 || y < 0 || x >= TileWidth || y >= TileHeight) return;

	HeightMap[x][y] = height;
}

float fun::GetTileHeightAt(int32 x, int32 y)
{
	if (x < 0 || y < 0 || x >= TileWidth || y >= TileHeight) return 0;

	return HeightMap[x][y];
}

void fun::SquareStep(int32 x1, int32 y1, int32 x2, int32 y2)
{
	int32 squareSize = x2 - x1;

	float centerHeight = 
		  GetTileHeightAt(x1, y1)
		+ GetTileHeightAt(x2, y1)
		+ GetTileHeightAt(x1, y2)
		+ GetTileHeightAt(x2, y2);

	centerHeight /= 4;

	centerHeight += FMath::FRandRange(-0.5f * squareSize, 0.5f * squareSize);

	SetTileHeightAt((x1 + x2) / 2, (y1 + y2) / 2, centerHeight);
}

void fun::DiamondStep(int32 x1, int32 y1, int32 x2, int32 y2)
{
	int32 squareSize = x2 - x1;

	float centerHeight = 
		  GetTileHeightAt(x1,				(y1 + y2) / 2)
		+ GetTileHeightAt(x2,				(y1 + y2) / 2)
		+ GetTileHeightAt((x1 + x2) / 2,	y1)
		+ GetTileHeightAt((x1 + x2) / 2,	y2);

	centerHeight /= 4;

	centerHeight += FMath::FRandRange(-0.5f * squareSize, 0.5f * squareSize);

	SetTileHeightAt((x1 + x2) / 2, (y1 + y2) / 2, centerHeight);
}