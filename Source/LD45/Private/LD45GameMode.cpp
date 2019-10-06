// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LD45GameMode.h"
#include "LD45GameMode.ac.h"

extends(AGameModeBase)

fun::ALD45GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALD45HUD::StaticClass();
}

mods(static) bool fun::GetCheatsEnabled()
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return true;
#endif
}