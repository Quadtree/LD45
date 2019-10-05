
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
#define fun         ALD45HUD
UTexture2D* ALD45HUD::GetCrosshairTex(){ return CrosshairTex; }
void ALD45HUD::SetCrosshairTex(UTexture2D* value){ CrosshairTex = value; }

#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "Public/LD45HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/NoExportTypes.h"
#include "CanvasItem.h"
