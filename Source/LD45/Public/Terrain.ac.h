
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
TSubclassOf<AActor> ATerrain::GetBushActorType(){ return BushActorType; }
void ATerrain::SetBushActorType(TSubclassOf<AActor> value){ BushActorType = value; }
int32 ATerrain::GetTrees(){ return Trees; }
void ATerrain::SetTrees(int32 value){ Trees = value; }
int32 ATerrain::GetBushes(){ return Bushes; }
void ATerrain::SetBushes(int32 value){ Bushes = value; }
float ATerrain::GetTreeLine(){ return TreeLine; }
void ATerrain::SetTreeLine(float value){ TreeLine = value; }

#include "LD45.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Templates/SubclassOf.h"
#include "Public/Terrain.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/UnrealString.h"
#include "UObject/NoExportTypes.h"
#include "EngineUtils.h"
#include "Public/LD45Character.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
