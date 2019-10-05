
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
UStaticMesh* ATerrain::GetTerrainCube(){ return TerrainCube; }
void ATerrain::SetTerrainCube(UStaticMesh* value){ TerrainCube = value; }
int32 ATerrain::GetTileWidth(){ return TileWidth; }
void ATerrain::SetTileWidth(int32 value){ TileWidth = value; }
int32 ATerrain::GetTileHeight(){ return TileHeight; }
void ATerrain::SetTileHeight(int32 value){ TileHeight = value; }

#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
