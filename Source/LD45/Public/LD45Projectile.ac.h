
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
#define fun         ALD45Projectile
UProjectileMovementComponent* ALD45Projectile::GetProjectileMovement(){ return ProjectileMovement; }
void ALD45Projectile::SetProjectileMovement(UProjectileMovementComponent* value){ ProjectileMovement = value; }
USphereComponent* ALD45Projectile::GetCollisionComp(){ return CollisionComp; }
void ALD45Projectile::SetCollisionComp(USphereComponent* value){ CollisionComp = value; }

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Public/LD45Projectile.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "UObject/NoExportTypes.h"
