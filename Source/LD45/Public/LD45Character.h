#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
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

	UFUNCTION(BlueprintCallable)
	void Interact(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void GainResources(TMap<EResourceType, float> resourcesToGain);

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

};
