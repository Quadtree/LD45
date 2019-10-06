#include "Terrain.h"
#include "Terrain.ac.h"

extends(AActor)

prop(UInstancedStaticMeshComponent* TerrainCubes)
prop(int32 TileWidth)
prop(int32 TileHeight)

prop(bare private TArray<TArray<float>> HeightMap)

prop(float HeightMultiplier)
prop(float TileSize)

prop(bare private TArray<TArray<float>> Jaggedness)

prop(TSubclassOf<AActor> TreeActorType)
prop(TSubclassOf<ABush> BushActorType)
prop(TSubclassOf<AActor> LightningBoltType)

prop(int32 Trees)
prop(int32 Bushes)

prop(float TreeLine)

prop(float LightningCooldown)

prop(FVector HighestPoint)

fun::ATerrain()
{
	TerrainCubes = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Cubes");
	RootComponent = TerrainCubes;
	HeightMultiplier = 30;
	TileSize = 100;
	PrimaryActorTick.bCanEverTick = true;
}

void fun::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	LightningCooldown = 0;

	for (int32 buildAttempt = 0; buildAttempt < 2000; ++buildAttempt)
	{
		Jaggedness.Empty();
		for (int32 x = 0; x < 8; ++x)
		{
			Jaggedness.Add(TArray<float>());
			for (int32 y = 0; y < 8; ++y)
			{
				Jaggedness[x].Add(FMath::Square(FMath::FRandRange(0, 5)) / FMath::Square(2));
			}
		}

		HeightMap.Empty();
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
					DiamondStep(x - squareSize / 2, y, x - squareSize / 2 + squareSize, y + squareSize);
					DiamondStep(x + squareSize / 2, y, x + squareSize / 2 + squareSize, y + squareSize);
					DiamondStep(x, y - squareSize / 2, x + squareSize, y - squareSize / 2 + squareSize);
					DiamondStep(x, y + squareSize / 2, x + squareSize, y + squareSize / 2 + squareSize);
				}
			}
		}

		int32 aboveWaterTiles = 0;
		int32 totalTiles = TileWidth * TileHeight;
		int32 tooHighEdgeTiles = 0;

		for (int32 x = 0; x < TileWidth; ++x)
		{
			for (int32 y = 0; y < TileHeight; ++y)
			{
				float height = HeightMap[x][y];

				int32 distToSide = FMath::Min(
					TileHeight - y,
					FMath::Min3(
						x,
						y,
						TileWidth - x
					)) * 2;

				//if (distToSide < 20) {
					if (height > distToSide) {
						++tooHighEdgeTiles;
						SetTileHeightAt(x, y, distToSide);
					}
					while (height > distToSide) {
						height = HeightMap[x][y];
						int32 cx = x + FMath::RandRange(-1, 1) * FMath::Square(FMath::RandRange(1, 4));
						int32 cy = y + FMath::RandRange(-1, 1) * FMath::Square(FMath::RandRange(1, 4));
						SetTileHeightAt(cx, cy, GetTileHeightAt(cx,cy) - FMath::FRandRange(0, 0.8f));
					}
				//}

				if (height >= 0) {
					++aboveWaterTiles;
				}
			}
		}

		UE_LOG(LogTemp, Display, TEXT("aboveWaterTiles=%s totalTiles=%s tooHighEdgeTiles=%s"), *FString::FromInt(aboveWaterTiles), *FString::FromInt(totalTiles), *FString::FromInt(tooHighEdgeTiles));

		if (aboveWaterTiles >= totalTiles / 2 && tooHighEdgeTiles < totalTiles / 10) break;
	}

	FVector startPoint;
	int32 n = 0;

	for (int32 x = 0; x < TileWidth; ++x)
	{
		for (int32 y = 0; y < TileHeight; ++y)
		{
			if (GetTileHeightAt(x, y) > 0)
			{
				FTransform trans;

				trans.SetComponents(
					FQuat::Identity,
					FVector(x * TileSize, y * TileSize, GetTileHeightAt(x, y) * HeightMultiplier),
					FVector(1 * TileSize / 100, 1 * TileSize / 100, 50)
				);

				TerrainCubes->AddInstance(trans);

				if (FMath::RandRange(0, n++) == 0)
				{
					startPoint = trans.GetLocation() + 27;

					if (startPoint.Z > HighestPoint.Z)
					{
						HighestPoint = startPoint;
					}
				}
			}
		}
	}

	for (TActorIterator<ALD45Character> i(GetWorld()); i; ++i)
	{
		i->SetActorLocation(startPoint);
	}

	for (int32 i=0;i<1000000 && Trees > 0;++i)
	{
		FVector pos = FVector(FMath::FRandRange(0, TileWidth * TileSize), FMath::FRandRange(0, TileWidth * TileSize), 10000);

		FHitResult res;

		if (GetWorld()->LineTraceSingleByObjectType(res, pos, pos - FVector(0, 0, 50000), FCollisionObjectQueryParams::AllObjects, FCollisionQueryParams()))
		{
			if (res.Actor == this && res.ImpactPoint.Z <= TreeLine)
			{
				GetWorld()->SpawnActor<AActor>(TreeActorType, res.ImpactPoint, FRotator::ZeroRotator);
				--Trees;
			}
		}
	}

	for (int32 i = 0; i < 1000000 && Bushes > 0; ++i)
	{
		FVector pos = FVector(FMath::FRandRange(0, TileWidth * TileSize), FMath::FRandRange(0, TileWidth * TileSize), 10000);

		FHitResult res;

		if (GetWorld()->LineTraceSingleByObjectType(res, pos, pos - FVector(0, 0, 50000), FCollisionObjectQueryParams::AllObjects, FCollisionQueryParams()))
		{
			if (res.Actor == this && res.ImpactPoint.Z <= TreeLine)
			{
				if (auto bush = GetWorld()->SpawnActor<ABush>(BushActorType, res.ImpactPoint, FRotator::ZeroRotator))
				{
					switch (FMath::RandRange(0, 2))
					{
					case 0: bush->SetBerryType(EResourceType::RT_RedBerries); break;
					case 1: bush->SetBerryType(EResourceType::RT_GreenBerries); break;
					case 2: bush->SetBerryType(EResourceType::RT_BlueBerries); break;
					}
					bush->BerryColorChanged();
					
					--Bushes;
				}
			}
		}
	}
}

void fun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	//UE_LOG(LogTemp, Display, TEXT("TICK"));

	if (LightningCooldown <= 0)
	{
		int32 treesOnFire = 0;
		AActor* randomTree = nullptr;
		int32 n = 0;

		for (TActorIterator<ATree> i(GetWorld()); i; ++i)
		{
			if (auto a = i->FindComponentByClass<UFlammableComponent>())
			{
				if (a->GetTemperature() > 200) treesOnFire++;
			}

			if (FMath::RandRange(0, n++) == 0)
			{
				randomTree = *i;
			}
		}

		UE_LOG(LogTemp, Display, TEXT("Trees on fire %s"), *FString::FromInt(treesOnFire));

		if (treesOnFire < 4 && randomTree)
		{
			UE_LOG(LogTemp, Display, TEXT("Lightning at %s"), *randomTree->GetName());
			GetWorld()->SpawnActor<AActor>(LightningBoltType, randomTree->GetActorLocation() + FVector(0, 0, 12000), FRotator::ZeroRotator);
			
		}

		LightningCooldown = 2;
	}
	
	LightningCooldown -= deltaTime;
}

void fun::SetTileHeightAt(int32 x, int32 y, float height)
{
	if (x < 0 || y < 0 || x >= TileWidth || y >= TileHeight) return;

	/*int32 distToSide = FMath::Min(
		TileHeight - y,
		FMath::Min3(
		x,
		y,
		TileWidth - x
	));

	if (distToSide < 5) {
		while (height > distToSide) {
			height -= FMath::FRandRange(0, 5);
		}
	}*/

	HeightMap[x][y] = height;
}

float fun::GetTileHeightAt(int32 x, int32 y)
{
	if (x < 0 || y < 0 || x >= TileWidth || y >= TileHeight) return 0;

	return HeightMap[x][y];
}

float fun::GetJaggednessAt(int32 x, int32 y)
{
	x = x * 8 / TileWidth;
	y = y * 8 / TileHeight;
	x = FMath::Clamp(x, 0, 7);
	y = FMath::Clamp(y, 0, 7);

	return Jaggedness[x][y];
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

	centerHeight += FMath::FRandRange(-0.5f * squareSize, 0.5f * squareSize) * GetJaggednessAt((x1 + x2) / 2, (y1 + y2) / 2);

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

	centerHeight += FMath::FRandRange(-0.5f * squareSize, 0.5f * squareSize) * GetJaggednessAt((x1 + x2) / 2, (y1 + y2) / 2);

	SetTileHeightAt((x1 + x2) / 2, (y1 + y2) / 2, centerHeight);
}