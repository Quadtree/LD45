#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Stick.generated.h"

UCLASS()
class LD45_API AStick : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetStaticMesh, BlueprintSetter=SetStaticMesh)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetHealth, BlueprintSetter=SetHealth)
	float Health;

public:
	AStick();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStaticMesh(class UStaticMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetHealth(float value);

};
