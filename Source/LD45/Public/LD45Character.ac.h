
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
#define fun         ALD45Character
float ALD45Character::GetBaseTurnRate(){ return BaseTurnRate; }
void ALD45Character::SetBaseTurnRate(float value){ BaseTurnRate = value; }
float ALD45Character::GetBaseLookUpRate(){ return BaseLookUpRate; }
void ALD45Character::SetBaseLookUpRate(float value){ BaseLookUpRate = value; }
UCameraComponent* ALD45Character::GetFirstPersonCameraComponent(){ return FirstPersonCameraComponent; }
void ALD45Character::SetFirstPersonCameraComponent(UCameraComponent* value){ FirstPersonCameraComponent = value; }
USkeletalMeshComponent* ALD45Character::GetMesh1P(){ return Mesh1P; }
void ALD45Character::SetMesh1P(USkeletalMeshComponent* value){ Mesh1P = value; }
USkeletalMeshComponent* ALD45Character::GetFP_Gun(){ return FP_Gun; }
void ALD45Character::SetFP_Gun(USkeletalMeshComponent* value){ FP_Gun = value; }
USceneComponent* ALD45Character::GetFP_MuzzleLocation(){ return FP_MuzzleLocation; }
void ALD45Character::SetFP_MuzzleLocation(USceneComponent* value){ FP_MuzzleLocation = value; }
FVector ALD45Character::GetGunOffset(){ return GunOffset; }
void ALD45Character::SetGunOffset(FVector value){ GunOffset = value; }
UMotionControllerComponent* ALD45Character::GetR_MotionController(){ return R_MotionController; }
void ALD45Character::SetR_MotionController(UMotionControllerComponent* value){ R_MotionController = value; }
UMotionControllerComponent* ALD45Character::GetL_MotionController(){ return L_MotionController; }
void ALD45Character::SetL_MotionController(UMotionControllerComponent* value){ L_MotionController = value; }
USkeletalMeshComponent* ALD45Character::GetVR_Gun(){ return VR_Gun; }
void ALD45Character::SetVR_Gun(USkeletalMeshComponent* value){ VR_Gun = value; }
USceneComponent* ALD45Character::GetVR_MuzzleLocation(){ return VR_MuzzleLocation; }
void ALD45Character::SetVR_MuzzleLocation(USceneComponent* value){ VR_MuzzleLocation = value; }
bool ALD45Character::GetbUsingMotionControllers(){ return bUsingMotionControllers; }
void ALD45Character::SetbUsingMotionControllers(bool value){ bUsingMotionControllers = value; }
TSubclassOf<AActor> ALD45Character::GetProjectileClass(){ return ProjectileClass; }
void ALD45Character::SetProjectileClass(TSubclassOf<AActor> value){ ProjectileClass = value; }
USoundBase* ALD45Character::GetFireSound(){ return FireSound; }
void ALD45Character::SetFireSound(USoundBase* value){ FireSound = value; }
TMap<EResourceType, float> ALD45Character::GetResources(){ return Resources; }
void ALD45Character::SetResources(TMap<EResourceType, float> value){ Resources = value; }
bool ALD45Character::GetIsInteracting(){ return IsInteracting; }
void ALD45Character::SetIsInteracting(bool value){ IsInteracting = value; }
AConstructible* ALD45Character::GetHeldConstructible(){ return HeldConstructible; }
void ALD45Character::SetHeldConstructible(AConstructible* value){ HeldConstructible = value; }
TSubclassOf<AConstructible> ALD45Character::GetConstructibleType(){ return ConstructibleType; }
void ALD45Character::SetConstructibleType(TSubclassOf<AConstructible> value){ ConstructibleType = value; }
float ALD45Character::GetConstructionCost(){ return ConstructionCost; }
void ALD45Character::SetConstructionCost(float value){ ConstructionCost = value; }
float ALD45Character::GetStickCost(){ return StickCost; }
void ALD45Character::SetStickCost(float value){ StickCost = value; }
TSubclassOf<AStick> ALD45Character::GetStickType(){ return StickType; }
void ALD45Character::SetStickType(TSubclassOf<AStick> value){ StickType = value; }
float ALD45Character::GetFood(){ return Food; }
void ALD45Character::SetFood(float value){ Food = value; }
float ALD45Character::GetTemperature(){ return Temperature; }
void ALD45Character::SetTemperature(float value){ Temperature = value; }
float ALD45Character::GetHealth(){ return Health; }
void ALD45Character::SetHealth(float value){ Health = value; }
TArray<EResourceType> ALD45Character::GetResourcesBeingEaten(){ return ResourcesBeingEaten; }
void ALD45Character::SetResourcesBeingEaten(TArray<EResourceType> value){ ResourcesBeingEaten = value; }
float ALD45Character::GetFoodConsumptionRate(){ return FoodConsumptionRate; }
void ALD45Character::SetFoodConsumptionRate(float value){ FoodConsumptionRate = value; }
float ALD45Character::GetFoodDamageRate(){ return FoodDamageRate; }
void ALD45Character::SetFoodDamageRate(float value){ FoodDamageRate = value; }
float ALD45Character::GetEmberLevel(){ return EmberLevel; }
void ALD45Character::SetEmberLevel(float value){ EmberLevel = value; }
float ALD45Character::GetMaxFood(){ return MaxFood; }
void ALD45Character::SetMaxFood(float value){ MaxFood = value; }
bool ALD45Character::GetIsGathering(){ return IsGathering; }
void ALD45Character::SetIsGathering(bool value){ IsGathering = value; }

#include "LD45.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/NoExportTypes.h"
#include "MotionControllerComponent.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Public/ResourceType.h"
#include "Public/Constructible.h"
#include "Public/Stick.h"
#include "Public/LD45Character.h"
#include "XRMotionControllerBase.h"
#include "Engine/EngineTypes.h"
#include "Components/InputComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Public/LD45Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/GameViewportClient.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/InputSettings.h"
#include "Engine/EngineBaseTypes.h"
#include "Public/FlammableComponent.h"
#include "Public/Tree.h"
#include "Public/Bush.h"
#include "Containers/UnrealString.h"
#include "Public/LD45GameMode.h"
#include "Public/BerrySecondaryEffect.h"
#include "GameFramework/Controller.h"
