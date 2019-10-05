#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "LD45Projectile.generated.h"

UCLASS()
class LD45_API ALD45Projectile : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetProjectileMovement, BlueprintSetter=SetProjectileMovement)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetCollisionComp, BlueprintSetter=SetCollisionComp)
	class USphereComponent* CollisionComp;

public:
	ALD45Projectile();

	UFUNCTION(BlueprintCallable)
	void OnHit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UProjectileMovementComponent* GetProjectileMovement();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetProjectileMovement(class UProjectileMovementComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USphereComponent* GetCollisionComp();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetCollisionComp(class USphereComponent* value);

};
