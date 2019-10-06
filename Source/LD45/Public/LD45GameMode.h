#pragma once

#include "EngineMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LD45GameMode.generated.h"

UCLASS()
class LD45_API ALD45GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALD45GameMode();

	UFUNCTION(BlueprintPure)
	static bool GetCheatsEnabled();

};
