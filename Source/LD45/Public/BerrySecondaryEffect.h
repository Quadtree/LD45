#pragma once
#include "EngineMinimal.h"

UENUM(BlueprintType)
enum class EBerrySecondaryEffect : uint8
{
	BSE_GainHealth,
	BSE_LoseHealth,
	BSE_GainTemperature,
	BSE_LoseTemperature,
	BSE_Max,
};
