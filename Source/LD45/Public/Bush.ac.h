
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
#define fun         ABush
UStaticMeshComponent* ABush::GetStaticMesh(){ return StaticMesh; }
void ABush::SetStaticMesh(UStaticMeshComponent* value){ StaticMesh = value; }
float ABush::GetMaxFood(){ return MaxFood; }
void ABush::SetMaxFood(float value){ MaxFood = value; }
float ABush::GetFoodRegenRate(){ return FoodRegenRate; }
void ABush::SetFoodRegenRate(float value){ FoodRegenRate = value; }
float ABush::GetFoodLeft(){ return FoodLeft; }
void ABush::SetFoodLeft(float value){ FoodLeft = value; }
EResourceType ABush::GetBerryType(){ return BerryType; }
void ABush::SetBerryType(EResourceType value){ BerryType = value; }
float ABush::GetHealth(){ return Health; }
void ABush::SetHealth(float value){ Health = value; }

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Public/ResourceType.h"
#include "Public/Bush.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Controller.h"
