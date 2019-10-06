#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "LD45.h"
#include "Public/ResourceType.h"
#include "Engine/EngineTypes.h"
#include "Engine/EngineBaseTypes.h"
#include "LD45Character.generated.h"

UCLASS()
class LD45_API ALD45Character : public ACharacter
{
	GENERATED_BODY()
private:
	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBaseTurnRate, BlueprintSetter=SetBaseTurnRate)
	float BaseTurnRate;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetBaseLookUpRate, BlueprintSetter=SetBaseLookUpRate)
	float BaseLookUpRate;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetFirstPersonCameraComponent, BlueprintSetter=SetFirstPersonCameraComponent)
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetMesh1P, BlueprintSetter=SetMesh1P)
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetFP_Gun, BlueprintSetter=SetFP_Gun)
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetFP_MuzzleLocation, BlueprintSetter=SetFP_MuzzleLocation)
	class USceneComponent* FP_MuzzleLocation;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetGunOffset, BlueprintSetter=SetGunOffset)
	FVector GunOffset;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetR_MotionController, BlueprintSetter=SetR_MotionController)
	class UMotionControllerComponent* R_MotionController;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetL_MotionController, BlueprintSetter=SetL_MotionController)
	class UMotionControllerComponent* L_MotionController;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetVR_Gun, BlueprintSetter=SetVR_Gun)
	class USkeletalMeshComponent* VR_Gun;

	UPROPERTY(SaveGame, VisibleAnywhere, BlueprintGetter=GetVR_MuzzleLocation, BlueprintSetter=SetVR_MuzzleLocation)
	class USceneComponent* VR_MuzzleLocation;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetbUsingMotionControllers, BlueprintSetter=SetbUsingMotionControllers)
	bool bUsingMotionControllers;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetProjectileClass, BlueprintSetter=SetProjectileClass)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFireSound, BlueprintSetter=SetFireSound)
	class USoundBase* FireSound;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetResources, BlueprintSetter=SetResources)
	TMap<EResourceType, float> Resources;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetIsInteracting, BlueprintSetter=SetIsInteracting)
	bool IsInteracting;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetHeldConstructible, BlueprintSetter=SetHeldConstructible)
	AConstructible* HeldConstructible;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetConstructibleType, BlueprintSetter=SetConstructibleType)
	TSubclassOf<AConstructible> ConstructibleType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetConstructionCost, BlueprintSetter=SetConstructionCost)
	float ConstructionCost;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetStickType, BlueprintSetter=SetStickType)
	TSubclassOf<AStick> StickType;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFood, BlueprintSetter=SetFood)
	float Food;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetTemperature, BlueprintSetter=SetTemperature)
	float Temperature;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetHealth, BlueprintSetter=SetHealth)
	float Health;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetResourcesBeingEaten, BlueprintSetter=SetResourcesBeingEaten)
	TArray<EResourceType> ResourcesBeingEaten;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFoodConsumptionRate, BlueprintSetter=SetFoodConsumptionRate)
	float FoodConsumptionRate;

	UPROPERTY(SaveGame, EditAnywhere, BlueprintGetter=GetFoodDamageRate, BlueprintSetter=SetFoodDamageRate)
	float FoodDamageRate;

public:
	ALD45Character();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	UFUNCTION(BlueprintCallable)
	void OnFire();

	UFUNCTION(BlueprintCallable)
	void OnResetVR();

	UFUNCTION(BlueprintCallable)
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	UFUNCTION(BlueprintCallable)
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void TurnAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	void LookUpAtRate(float Rate);

	UFUNCTION(BlueprintCallable)
	bool EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent);

	bool DoConstructibleQuery(FHitResult& res);

	void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void InteractAxis(float amount);

	UFUNCTION(BlueprintCallable)
	void Interact(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void GainResources(TMap<EResourceType, float> resourcesToGain);

	UFUNCTION(BlueprintCallable)
	void BeginConstruction();

	UFUNCTION(BlueprintCallable)
	void PlaceConstructible();

	UFUNCTION(BlueprintCallable)
	void CancelConstruction();

	UFUNCTION(BlueprintPure)
	float GetAmountOfResource(EResourceType resourceType);

	UFUNCTION(BlueprintCallable)
	void EatResource(EResourceType resourceType, float deltaTime);

	UFUNCTION(BlueprintCallable)
	void EatRedBerriesAxis(float axisValue);

	UFUNCTION(BlueprintCallable)
	void EatGreenBerriesAxis(float axisValue);

	UFUNCTION(BlueprintCallable)
	void EatBlueBerriesAxis(float axisValue);

	UFUNCTION(BlueprintCallable)
	void LightObject();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void DropStick();

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetBaseTurnRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBaseTurnRate(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetBaseLookUpRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetBaseLookUpRate(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UCameraComponent* GetFirstPersonCameraComponent();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFirstPersonCameraComponent(class UCameraComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USkeletalMeshComponent* GetMesh1P();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetMesh1P(class USkeletalMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USkeletalMeshComponent* GetFP_Gun();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFP_Gun(class USkeletalMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USceneComponent* GetFP_MuzzleLocation();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFP_MuzzleLocation(class USceneComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	FVector GetGunOffset();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetGunOffset(FVector value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UMotionControllerComponent* GetR_MotionController();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetR_MotionController(class UMotionControllerComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class UMotionControllerComponent* GetL_MotionController();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetL_MotionController(class UMotionControllerComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USkeletalMeshComponent* GetVR_Gun();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetVR_Gun(class USkeletalMeshComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USceneComponent* GetVR_MuzzleLocation();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetVR_MuzzleLocation(class USceneComponent* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	bool GetbUsingMotionControllers();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetbUsingMotionControllers(bool value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AActor>  GetProjectileClass();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetProjectileClass(TSubclassOf<AActor> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	class USoundBase* GetFireSound();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFireSound(class USoundBase* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TMap<EResourceType, float> GetResources();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetResources(TMap<EResourceType, float> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	bool GetIsInteracting();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetIsInteracting(bool value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	AConstructible*  GetHeldConstructible();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetHeldConstructible(AConstructible* value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AConstructible>  GetConstructibleType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetConstructibleType(TSubclassOf<AConstructible> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetConstructionCost();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetConstructionCost(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TSubclassOf<AStick>  GetStickType();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetStickType(TSubclassOf<AStick> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetFood();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFood(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetTemperature();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetTemperature(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetHealth(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	TArray<EResourceType> GetResourcesBeingEaten();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetResourcesBeingEaten(TArray<EResourceType> value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetFoodConsumptionRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFoodConsumptionRate(float value);

	UFUNCTION(BlueprintGetter, BlueprintPure)
	float GetFoodDamageRate();

	UFUNCTION(BlueprintSetter, BlueprintCallable)
	void SetFoodDamageRate(float value);

};
