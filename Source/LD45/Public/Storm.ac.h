
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
UParticleSystemComponent* AStorm::GetRainParticleSystem(){ return RainParticleSystem; }
void AStorm::SetRainParticleSystem(UParticleSystemComponent* value){ RainParticleSystem = value; }
USceneComponent* AStorm::GetSceneComp(){ return SceneComp; }
void AStorm::SetSceneComp(USceneComponent* value){ SceneComp = value; }
FVector AStorm::GetStormVector(){ return StormVector; }
void AStorm::SetStormVector(FVector value){ StormVector = value; }

#include "LD45.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/NoExportTypes.h"
#include "Public/Storm.h"
#include "Engine/EngineTypes.h"
#include "Containers/UnrealString.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Public/LD45Character.h"
#include "Public/FlammableComponent.h"
#include "CollisionQueryParams.h"
