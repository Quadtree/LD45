#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LD45.h"
#include "Public/ResourceType.h"
#include "Public/BerrySecondaryEffect.h"
#include "LD45GameMode.generated.h"

UCLASS()
class LD45_API ALD45GameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBerrySecondaryEffects, BlueprintSetter=SetBerrySecondaryEffects)
	TMap<EResourceType, EBerrySecondaryEffect> BerrySecondaryEffects;

public:
	ALD45GameMode();

	void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	static bool GetCheatsEnabled();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TMap<EResourceType, EBerrySecondaryEffect> GetBerrySecondaryEffects();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBerrySecondaryEffects(TMap<EResourceType, EBerrySecondaryEffect> value);

};
