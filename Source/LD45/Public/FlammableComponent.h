#pragma once

#include "EngineMinimal.h"
#include "Components/ActorComponent.h"
#include "LD45.h"
#include "Engine/EngineBaseTypes.h"
#include "FlammableComponent.generated.h"

UCLASS(meta=(BlueprintSpawnableComponent))
class LD45_API UFlammableComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTemperature, BlueprintSetter=SetTemperature)
	float Temperature;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetMass, BlueprintSetter=SetMass)
	float Mass;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetDamageRate, BlueprintSetter=SetDamageRate)
	float DamageRate;

public:
	UFlammableComponent();

	UFUNCTION(BlueprintPure)
	float GetHeatProduced();

	UFUNCTION(BlueprintPure)
	float GetMass();

	UFUNCTION(BlueprintCallable)
	void AddHeat(float roughJoules, float max);

	void TickComponent(float deltaTime, enum ELevelTick TickType, struct FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetTemperature();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTemperature(float value);

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetMass(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetDamageRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetDamageRate(float value);

};
