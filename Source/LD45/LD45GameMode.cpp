// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LD45GameMode.h"
#include "LD45HUD.h"
#include "LD45Character.h"
#include "UObject/ConstructorHelpers.h"

ALD45GameMode::ALD45GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALD45HUD::StaticClass();
}
