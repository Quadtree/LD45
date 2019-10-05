#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Terrain.generated.h"

UCLASS()
class LD45_API ATerrain : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetTerrainCubes, BlueprintSetter=SetTerrainCubes)
	class UInstancedStaticMeshComponent* TerrainCubes;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTileWidth, BlueprintSetter=SetTileWidth)
	int32 TileWidth;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTileHeight, BlueprintSetter=SetTileHeight)
	int32 TileHeight;

public:
	ATerrain();

	UFUNCTION(BlueprintCallable)
	void BeginPlay();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UInstancedStaticMeshComponent* GetTerrainCubes();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTerrainCubes(class UInstancedStaticMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	int32 GetTileWidth();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTileWidth(int32 value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	int32 GetTileHeight();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTileHeight(int32 value);

};
