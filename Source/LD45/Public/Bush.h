#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/ResourceType.h"
#include "Public/ResourceType.h"
#include "Public/ResourceType.h"
#include "Bush.generated.h"

UCLASS()
class LD45_API ABush : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetStaticMesh, BlueprintSetter=SetStaticMesh)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetMaxFood, BlueprintSetter=SetMaxFood)
	float MaxFood;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFoodRegenRate, BlueprintSetter=SetFoodRegenRate)
	float FoodRegenRate;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFoodLeft, BlueprintSetter=SetFoodLeft)
	float FoodLeft;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBerryType, BlueprintSetter=SetBerryType)
	EResourceType BerryType;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void BerryColorChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void ConsiderBerryVisibility();

	ABush();

	TMap<EResourceType, float> Harvest(float harvestSpeed);

	void BeginPlay() override;

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStaticMesh(class UStaticMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetMaxFood();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetMaxFood(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetFoodRegenRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFoodRegenRate(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetFoodLeft();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFoodLeft(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	EResourceType GetBerryType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBerryType(EResourceType value);

};
