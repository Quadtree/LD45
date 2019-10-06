
#ifdef fun
    #undef fun
#endif

#define mods(...)
#define im(...)
#define blueprintEvent(...)
#define prop(...)
#define extends(...)
#define classMods(...)
#define delegateVoid(...)
#define fun         AStorm
float AStorm::GetStormLevel(){ return StormLevel; }
void AStorm::SetStormLevel(float value){ StormLevel = value; }
float AStorm::GetMaxStormLevel(){ return MaxStormLevel; }
void AStorm::SetMaxStormLevel(float value){ MaxStormLevel = value; }
float AStorm::GetStormOverallPower(){ return StormOverallPower; }
void AStorm::SetStormOverallPower(float value){ StormOverallPower = value; }
bool AStorm::GetStormLevelRising(){ return StormLevelRising; }
void AStorm::SetStormLevelRising(bool value){ StormLevelRising = value; }

#include "LD45.h"
#include "GameFramework/Actor.h"
#include "Containers/UnrealString.h"
#include "Math/UnrealMathUtility.h"
