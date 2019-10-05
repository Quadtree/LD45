#pragma once

#include "EngineMinimal.h"
#include "GameFramework/HUD.h"
#include "LD45HUD.generated.h"

UCLASS()
class LD45_API ALD45HUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetCrosshairTex, BlueprintSetter=SetCrosshairTex)
	class UTexture2D* CrosshairTex;

public:
	ALD45HUD();

	void DrawHUD() override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UTexture2D* GetCrosshairTex();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetCrosshairTex(class UTexture2D* value);

};
