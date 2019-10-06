#include "Storm.h"
#include "Storm.ac.h"

extends(AActor)

prop(float StormLevel)
prop(float MaxStormLevel)
prop(bool StormLevelRising)

void fun::StartStorm(float maxLevel)
{
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
}