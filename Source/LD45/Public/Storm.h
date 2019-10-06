#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Storm.generated.h"

UCLASS()
class LD45_API AStorm : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStormLevel, BlueprintSetter=SetStormLevel)
	float StormLevel;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetMaxStormLevel, BlueprintSetter=SetMaxStormLevel)
	float MaxStormLevel;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStormLevelRising, BlueprintSetter=SetStormLevelRising)
	bool StormLevelRising;

public:
	UFUNCTION(BlueprintCallable)
	void StartStorm(float maxLevel);

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetStormLevel();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormLevel(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetMaxStormLevel();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetMaxStormLevel(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	bool GetStormLevelRising();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormLevelRising(bool value);

};
