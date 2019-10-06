
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
#define fun         ATerrain
UInstancedStaticMeshComponent* ATerrain::GetTerrainCubes(){ return TerrainCubes; }
void ATerrain::SetTerrainCubes(UInstancedStaticMeshComponent* value){ TerrainCubes = value; }
int32 ATerrain::GetTileWidth(){ return TileWidth; }
void ATerrain::SetTileWidth(int32 value){ TileWidth = value; }
int32 ATerrain::GetTileHeight(){ return TileHeight; }
void ATerrain::SetTileHeight(int32 value){ TileHeight = value; }
float ATerrain::GetHeightMultiplier(){ return HeightMultiplier; }
void ATerrain::SetHeightMultiplier(float value){ HeightMultiplier = value; }
float ATerrain::GetTileSize(){ return TileSize; }
void ATerrain::SetTileSize(float value){ TileSize = value; }
TSubclassOf<AActor> ATerrain::GetTreeActorType(){ return TreeActorType; }
void ATerrain::SetTreeActorType(TSubclassOf<AActor> value){ TreeActorType = value; }
TSubclassOf<ABush> ATerrain::GetBushActorType(){ return BushActorType; }
void ATerrain::SetBushActorType(TSubclassOf<ABush> value){ BushActorType = value; }
TSubclassOf<AActor> ATerrain::GetLightningBoltType(){ return LightningBoltType; }
void ATerrain::SetLightningBoltType(TSubclassOf<AActor> value){ LightningBoltType = value; }
TSubclassOf<AActor> ATerrain::GetRescuePlaneType(){ return RescuePlaneType; }
void ATerrain::SetRescuePlaneType(TSubclassOf<AActor> value){ RescuePlaneType = value; }
int32 ATerrain::GetTrees(){ return Trees; }
void ATerrain::SetTrees(int32 value){ Trees = value; }
int32 ATerrain::GetBushes(){ return Bushes; }
void ATerrain::SetBushes(int32 value){ Bushes = value; }
float ATerrain::GetTreeLine(){ return TreeLine; }
void ATerrain::SetTreeLine(float value){ TreeLine = value; }
float ATerrain::GetLightningCooldown(){ return LightningCooldown; }
void ATerrain::SetLightningCooldown(float value){ LightningCooldown = value; }
float ATerrain::GetRescuePlaneCooldown(){ return RescuePlaneCooldown; }
void ATerrain::SetRescuePlaneCooldown(float value){ RescuePlaneCooldown = value; }
FVector ATerrain::GetHighestPoint(){ return HighestPoint; }
void ATerrain::SetHighestPoint(FVector value){ HighestPoint = value; }

#include "LD45.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Templates/SubclassOf.h"
#include "Public/Bush.h"
#include "UObject/NoExportTypes.h"
#include "Public/Terrain.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"
#include "EngineUtils.h"
#include "Public/LD45Character.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "Public/ResourceType.h"
#include "Public/Tree.h"
#include "Public/FlammableComponent.h"
