
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
#define fun         UFlammableComponent
float UFlammableComponent::GetTemperature(){ return Temperature; }
void UFlammableComponent::SetTemperature(float value){ Temperature = value; }
float UFlammableComponent::GetMass(){ return Mass; }
void UFlammableComponent::SetMass(float value){ Mass = value; }

#include "LD45.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Public/FlammableComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/EngineTypes.h"
#include "UObject/NoExportTypes.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "Math/UnrealMathUtility.h"
#include "Particles/ParticleSystemComponent.h"
