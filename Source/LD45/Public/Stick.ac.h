
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
#define fun         AStick
UStaticMeshComponent* AStick::GetStaticMesh(){ return StaticMesh; }
void AStick::SetStaticMesh(UStaticMeshComponent* value){ StaticMesh = value; }
float AStick::GetHealth(){ return Health; }
void AStick::SetHealth(float value){ Health = value; }

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Public/Stick.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Controller.h"
