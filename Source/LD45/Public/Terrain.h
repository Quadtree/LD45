#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "LD45.h"
#include "Public/ResourceType.h"
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

	TArray<TArray<float>> HeightMap;

	TArray<TArray<int32>> DistToCenter;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetHeightMultiplier, BlueprintSetter=SetHeightMultiplier)
	float HeightMultiplier;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTileSize, BlueprintSetter=SetTileSize)
	float TileSize;

	TArray<TArray<float>> Jaggedness;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTreeActorType, BlueprintSetter=SetTreeActorType)
	TSubclassOf<AActor> TreeActorType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBushActorType, BlueprintSetter=SetBushActorType)
	TSubclassOf<ABush> BushActorType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetLightningBoltType, BlueprintSetter=SetLightningBoltType)
	TSubclassOf<AActor> LightningBoltType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetRescuePlaneType, BlueprintSetter=SetRescuePlaneType)
	TSubclassOf<AActor> RescuePlaneType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTrees, BlueprintSetter=SetTrees)
	int32 Trees;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBushes, BlueprintSetter=SetBushes)
	int32 Bushes;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTreeLine, BlueprintSetter=SetTreeLine)
	float TreeLine;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetLightningCooldown, BlueprintSetter=SetLightningCooldown)
	float LightningCooldown;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetRescuePlaneCooldown, BlueprintSetter=SetRescuePlaneCooldown)
	float RescuePlaneCooldown;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetHighestPoint, BlueprintSetter=SetHighestPoint)
	FVector HighestPoint;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ResucePlane();

	ATerrain();

	void BeginPlay() override;

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetTileHeightAt(int32 x, int32 y, float height);

	UFUNCTION(BlueprintPure)
	float GetTileHeightAt(int32 x, int32 y);

	UFUNCTION(BlueprintPure)
	float GetJaggednessAt(int32 x, int32 y);

	UFUNCTION(BlueprintCallable)
	void SquareStep(int32 x1, int32 y1, int32 x2, int32 y2);

	UFUNCTION(BlueprintCallable)
	void DiamondStep(int32 x1, int32 y1, int32 x2, int32 y2);

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

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetHeightMultiplier();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetHeightMultiplier(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetTileSize();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTileSize(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AActor>  GetTreeActorType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTreeActorType(TSubclassOf<AActor> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<ABush>  GetBushActorType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBushActorType(TSubclassOf<ABush> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AActor>  GetLightningBoltType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetLightningBoltType(TSubclassOf<AActor> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AActor>  GetRescuePlaneType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetRescuePlaneType(TSubclassOf<AActor> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	int32 GetTrees();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTrees(int32 value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	int32 GetBushes();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBushes(int32 value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetTreeLine();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTreeLine(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetLightningCooldown();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetLightningCooldown(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetRescuePlaneCooldown();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetRescuePlaneCooldown(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	FVector GetHighestPoint();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetHighestPoint(FVector value);

};
