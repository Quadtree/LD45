#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "LD45.h"
#include "Engine/EngineTypes.h"
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

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStormOverallPower, BlueprintSetter=SetStormOverallPower)
	float StormOverallPower;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStormLevelRising, BlueprintSetter=SetStormLevelRising)
	bool StormLevelRising;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetRainParticleSystem, BlueprintSetter=SetRainParticleSystem)
	class UParticleSystemComponent* RainParticleSystem;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetSceneComp, BlueprintSetter=SetSceneComp)
	class USceneComponent* SceneComp;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStormVector, BlueprintSetter=SetStormVector)
	FVector StormVector;

public:
	AStorm();

	UFUNCTION(BlueprintCallable)
	void StartStorm(float maxLevel);

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PotentiallyChill(class AActor* actor, float deltaTime);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetStormLevel();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormLevel(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetMaxStormLevel();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetMaxStormLevel(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetStormOverallPower();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormOverallPower(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	bool GetStormLevelRising();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormLevelRising(bool value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UParticleSystemComponent* GetRainParticleSystem();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetRainParticleSystem(class UParticleSystemComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USceneComponent* GetSceneComp();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetSceneComp(class USceneComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	FVector GetStormVector();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStormVector(FVector value);

};
