// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LD45GameMode.h"
#include "LD45GameMode.ac.h"

extends(AGameModeBase)

prop(TMap<EResourceType, EBerrySecondaryEffect> BerrySecondaryEffects)

fun::ALD45GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALD45HUD::StaticClass();
}

void fun::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("GameMode BeginPlay()"));

	TArray<EResourceType> berryTypes;
	berryTypes.Add(EResourceType::RT_RedBerries);
	berryTypes.Add(EResourceType::RT_GreenBerries);
	berryTypes.Add(EResourceType::RT_BlueBerries);

	for (auto bt : berryTypes)
	{
		BerrySecondaryEffects.Add(bt, ( EBerrySecondaryEffect) FMath::RandRange(0, (int32)EBerrySecondaryEffect::BSE_Max - 1));
		UE_LOG(LogTemp, Display, TEXT("BerrySecondaryEffect %s=%s"), *FString::FromInt(( int32) bt), *FString::FromInt((int32)BerrySecondaryEffects[bt]));
	}
}

mods(static) bool fun::GetCheatsEnabled()
{
#if UE_BUILD_SHIPPING
	return false;
#else
	return true;
#endif
}