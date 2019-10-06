#include "Storm.h"
#include "Storm.ac.h"

extends(AActor)

prop(float StormLevel)
prop(float MaxStormLevel)
prop(float StormOverallPower)
prop(bool StormLevelRising)

void fun::StartStorm(float maxLevel)
{
	UE_LOG(LogTemp, Display, TEXT("Storm starting at power %s"), *FString::SanitizeFloat(maxLevel));

	MaxStormLevel = maxLevel;
	StormLevelRising = true;
}

void fun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (MaxStormLevel > 0.1f)
	{
		if (StormLevelRising)
		{
			if (StormLevel < MaxStormLevel)
			{
				StormLevel = FMath::Clamp(StormLevel + deltaTime * MaxStormLevel / 30.f, 0.f, MaxStormLevel);
			}
			else
			{
				StormLevelRising = false;
			}
		}
		else
		{
			StormLevel = FMath::Clamp(StormLevel - deltaTime * MaxStormLevel / 30.f, 0.f, MaxStormLevel);
		}
	}

	if (FMath::FRand() < StormOverallPower * deltaTime)
	{
		StartStorm(StormOverallPower * 5);
	}
}