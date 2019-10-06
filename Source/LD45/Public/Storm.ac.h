
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
bool AStorm::GetStormLevelRising(){ return StormLevelRising; }
void AStorm::SetStormLevelRising(bool value){ StormLevelRising = value; }

#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
