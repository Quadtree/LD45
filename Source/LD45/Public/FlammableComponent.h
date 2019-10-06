#pragma once

#include "EngineMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/EngineTypes.h"
#include "FlammableComponent.generated.h"

UCLASS()
class LD45_API UFlammableComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTemperature, BlueprintSetter=SetTemperature)
	float Temperature;

public:
	UFlammableComponent();

	UFUNCTION(BlueprintCallable)
	void AddHeat(float roughJoules);

	UFUNCTION(BlueprintPure)
	float GetMass();

	void TickComponent(float deltaTime, enum ELevelTick TickType, struct FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetTemperature();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTemperature(float value);

};
