#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Constructible.generated.h"

UCLASS()
class LD45_API AConstructible : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetWoodCost, BlueprintSetter=SetWoodCost)
	float WoodCost;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetStaticMesh, BlueprintSetter=SetStaticMesh)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetSceneComp, BlueprintSetter=SetSceneComp)
	class USceneComponent* SceneComp;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BecomeSolid();

	AConstructible();

	void SetForConstructionAt(AActor* constructor, const FHitResult& res);

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlaceConstructible();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetWoodCost();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetWoodCost(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStaticMesh(class UStaticMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USceneComponent* GetSceneComp();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetSceneComp(class USceneComponent* value);

};
