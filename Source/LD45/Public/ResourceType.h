#pragma once
#include "EngineMinimal.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	RT_Wood,
	RT_RedBerries,
	RT_GreenBerries,
	RT_BlueBerries,
	RT_Max,
};
