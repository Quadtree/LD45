#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/ResourceType.h"
#include "Tree.generated.h"

UCLASS()
class LD45_API ATree : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetStaticMesh, BlueprintSetter=SetStaticMesh)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetWoodLeft, BlueprintSetter=SetWoodLeft)
	float WoodLeft;

public:
	ATree();

	TMap<EResourceType, float> Harvest(float harvestSpeed);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStaticMesh(class UStaticMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetWoodLeft();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetWoodLeft(float value);

};
