
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
#define fun         AConstructible
float AConstructible::GetWoodCost(){ return WoodCost; }
void AConstructible::SetWoodCost(float value){ WoodCost = value; }
UStaticMeshComponent* AConstructible::GetStaticMesh(){ return StaticMesh; }
void AConstructible::SetStaticMesh(UStaticMeshComponent* value){ StaticMesh = value; }
USceneComponent* AConstructible::GetSceneComp(){ return SceneComp; }
void AConstructible::SetSceneComp(USceneComponent* value){ SceneComp = value; }
float AConstructible::GetHealth(){ return Health; }
void AConstructible::SetHealth(float value){ Health = value; }

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Public/Constructible.h"
#include "Engine/EngineTypes.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Controller.h"
