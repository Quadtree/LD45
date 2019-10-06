
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
#define fun         ATree
UStaticMeshComponent* ATree::GetStaticMesh(){ return StaticMesh; }
void ATree::SetStaticMesh(UStaticMeshComponent* value){ StaticMesh = value; }
float ATree::GetWoodLeft(){ return WoodLeft; }
void ATree::SetWoodLeft(float value){ WoodLeft = value; }

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Public/Tree.h"
#include "Public/ResourceType.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Controller.h"
