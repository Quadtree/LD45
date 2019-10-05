
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

#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Public/Terrain.h"
#include "UObject/NoExportTypes.h"
