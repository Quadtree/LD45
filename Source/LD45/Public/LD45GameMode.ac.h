
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
#define fun         ALD45GameMode
TMap<EResourceType, EBerrySecondaryEffect> ALD45GameMode::GetBerrySecondaryEffects(){ return BerrySecondaryEffects; }
void ALD45GameMode::SetBerrySecondaryEffects(TMap<EResourceType, EBerrySecondaryEffect> value){ BerrySecondaryEffects = value; }

#include "LD45.h"
#include "GameFramework/GameModeBase.h"
#include "Public/ResourceType.h"
#include "Public/BerrySecondaryEffect.h"
#include "Public/LD45GameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Pawn.h"
#include "Public/LD45HUD.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"
