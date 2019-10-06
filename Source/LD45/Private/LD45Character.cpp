// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LD45Character.h"
#include "LD45Character.ac.h"

extends(ACharacter)

prop(float BaseTurnRate)
prop(float BaseLookUpRate)
prop(UCameraComponent* FirstPersonCameraComponent)
prop(USkeletalMeshComponent* Mesh1P)
prop(USkeletalMeshComponent* FP_Gun)
prop(USceneComponent* FP_MuzzleLocation)
prop(FVector GunOffset)
prop(UMotionControllerComponent* R_MotionController)
prop(UMotionControllerComponent* L_MotionController)
prop(USkeletalMeshComponent* VR_Gun)
prop(USceneComponent* VR_MuzzleLocation)
prop(bool bUsingMotionControllers)
prop(TSubclassOf<AActor> ProjectileClass)
prop(USoundBase* FireSound)
prop(TMap<EResourceType, float> Resources)
prop(bool IsInteracting)

prop(AConstructible* HeldConstructible)
prop(TSubclassOf<AConstructible> ConstructibleType)
prop(float ConstructionCost)
prop(float StickCost)
prop(TSubclassOf<AStick> StickType)

prop(float Food)
prop(float Temperature)
prop(float Health)

prop(TArray<EResourceType> ResourcesBeingEaten)

prop(float FoodConsumptionRate)
prop(float FoodDamageRate)
prop(float EmberLevel)

prop(float MaxFood)

prop(bool IsGathering)

blueprintEvent(IgniteSomething)
blueprintEvent(Construct)

blueprintEvent(OnDeath)

blueprintEvent(CantConstruct)
blueprintEvent(CantCreateStick)
blueprintEvent(CantCreateFire)
blueprintEvent(CantEat)
blueprintEvent(OnStarving)
blueprintEvent(OnOverheating)
blueprintEvent(OnFreezing)

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ALD45Character

fun::ALD45Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void fun::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void fun::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALD45Character::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALD45Character::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ALD45Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALD45Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALD45Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALD45Character::LookUpAtRate);

	PlayerInputComponent->BindAxis("Interact", this, &ALD45Character::InteractAxis);

	PlayerInputComponent->BindAxis("EatRedBerries", this, &ALD45Character::EatRedBerriesAxis);
	PlayerInputComponent->BindAxis("EatGreenBerries", this, &ALD45Character::EatGreenBerriesAxis);
	PlayerInputComponent->BindAxis("EatBlueBerries", this, &ALD45Character::EatBlueBerriesAxis);

	PlayerInputComponent->BindAction("BeginConstruction", IE_Pressed, this, &ALD45Character::BeginConstruction);
	PlayerInputComponent->BindAction("CancelConstruction", IE_Pressed, this, &ALD45Character::CancelConstruction);

	PlayerInputComponent->BindAction("LightObject", IE_Pressed, this, &ALD45Character::LightObject);

	PlayerInputComponent->BindAction("DropStick", IE_Pressed, this, &ALD45Character::DropStick);
}

void fun::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<ALD45Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<ALD45Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	/*if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}*/
}

void fun::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void fun::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	/*if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;*/
}

void fun::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	/*if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;*/
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ALD45Character::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void fun::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void fun::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void fun::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void fun::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool fun::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ALD45Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ALD45Character::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ALD45Character::TouchUpdate);
		return true;
	}

	return false;
}

mods(bare) bool fun::DoConstructibleQuery(FHitResult& res)
{
	FVector rayStart = FindComponentByClass<UCameraComponent>()->GetComponentLocation();
	FRotator rayDir = FindComponentByClass<UCameraComponent>()->GetComponentRotation();

	return GetWorld()->LineTraceSingleByChannel(res, rayStart, rayStart + rayDir.RotateVector(FVector(700, 0, 0)), ECollisionChannel::ECC_Visibility);
}

void fun::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	IsGathering = false;

	if (IsInteracting)
	{
		Interact(deltaTime);
	}

	if (HeldConstructible)
	{
		FHitResult res;
		if (DoConstructibleQuery(res))
		{
			HeldConstructible->SetForConstructionAt(this, res);
		}
		else
		{
			HeldConstructible->SetActorLocation(FVector(0, 0, -50000));
		}
	}

	for (auto eaten : ResourcesBeingEaten)
	{
		EatResource(eaten, deltaTime);
		break;
	}

	Food -= FoodConsumptionRate * deltaTime;

	if (Food < 0)
	{
		Health += Food * FoodDamageRate;
		Food = 0;
		OnStarving();
	}

	if (FindComponentByClass<UFlammableComponent>()->GetTemperature() >= 46) OnOverheating();
	if (FindComponentByClass<UFlammableComponent>()->GetTemperature() <= 0) OnFreezing();

	if (GetActorLocation().Z < 50)
	{
		FindComponentByClass<UFlammableComponent>()->SetTemperature(FindComponentByClass<UFlammableComponent>()->GetTemperature() - 12 * deltaTime);
	}

	float curTemp = FindComponentByClass<UFlammableComponent>()->GetTemperature();

	float tempDamageRate = FMath::Max(FMath::Abs(curTemp - 23) - 25, 0.f);

	TakeDamage(tempDamageRate * deltaTime, FDamageEvent(), nullptr, nullptr);
}

void fun::InteractAxis(float amount)
{
	IsInteracting = amount > 0.01f;
}

void fun::Interact(float deltaTime)
{
	FHitResult res;

	if (!HeldConstructible)
	{
		FVector rayStart = FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		FRotator rayDir = FindComponentByClass<UCameraComponent>()->GetComponentRotation();

		if (GetWorld()->LineTraceSingleByChannel(res, rayStart, rayStart + rayDir.RotateVector(FVector(500, 0, 0)), ECollisionChannel::ECC_Visibility))
		{
			if (res.Actor.IsValid())
			{
				if (auto a = res.Actor->FindComponentByClass<UFlammableComponent>())
				{
					if (a->GetTemperature() > 300)
					{
						EmberLevel = 1.f;
					}
				}

				if (auto a = Cast<ATree>(res.Actor))
				{
					GainResources(a->Harvest(35 * deltaTime));
					IsGathering = true;
				}
				else if (auto a = Cast<ABush>(res.Actor))
				{
					if (a->GetFoodLeft() > 0)
					{
						GainResources(a->Harvest(10 * deltaTime));
						IsGathering = true;
					}
				}
				
			}
		}
	}
	else
	{
		if (DoConstructibleQuery(res))
		{
			Construct();
			HeldConstructible->PlaceConstructible();
			HeldConstructible = nullptr;
		}
	}
}

void fun::GainResources(TMap<EResourceType, float> resourcesToGain)
{
	for (auto kv : resourcesToGain)
	{
		if (!Resources.Contains(kv.Key)) Resources.Add(kv.Key, 0);
		Resources[kv.Key] += kv.Value;
		UE_LOG(LogTemp, Display, TEXT("Gained %s %s, new value is %s"), *FString::SanitizeFloat(kv.Value), *FString::FromInt((int32)kv.Key), *FString::SanitizeFloat(Resources[kv.Key]));
	}
}

void fun::BeginConstruction()
{
	if (HeldConstructible) return;

	if (Resources.Contains(EResourceType::RT_Wood) && Resources[EResourceType::RT_Wood] >= ConstructionCost)
	{
		Resources[EResourceType::RT_Wood] -= ConstructionCost;
		HeldConstructible = GetWorld()->SpawnActor<AConstructible>(ConstructibleType, FVector(0, 0, -40000), FRotator::ZeroRotator);
	}
	else
	{
		CantConstruct();
	}
}

void fun::PlaceConstructible()
{

}

void fun::CancelConstruction()
{
	if (!HeldConstructible) return;

	HeldConstructible->Destroy();
	HeldConstructible = nullptr;

	if (!Resources.Contains(EResourceType::RT_Wood)) Resources.Add(EResourceType::RT_Wood, 0);
	Resources[EResourceType::RT_Wood] += ConstructionCost;
}

float fun::GetAmountOfResource(EResourceType resourceType)
{
	if (Resources.Contains(resourceType)) return Resources[resourceType];
	return 0;
}

void fun::EatResource(EResourceType resourceType, float deltaTime)
{
	if (!Resources.Contains(resourceType)) Resources.Add(resourceType, 0);

	float eaten = FMath::Clamp(deltaTime * 10, 0.f, Resources[resourceType]);

	if (eaten <= 0.01) CantEat();

	Resources[resourceType] -= eaten;
	Food = FMath::Clamp(Food + eaten, 0.f, MaxFood);

	if (auto gm = Cast<ALD45GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		auto fc = FindComponentByClass<UFlammableComponent>();

		switch (gm->GetBerrySecondaryEffects()[resourceType])
		{
		case EBerrySecondaryEffect::BSE_GainHealth: Health = FMath::Clamp(Health + eaten * 3, 0.f, 100.f); break;
		case EBerrySecondaryEffect::BSE_LoseHealth: Health = FMath::Clamp(Health - eaten * 3, 0.f, 100.f); break;
		case EBerrySecondaryEffect::BSE_LoseTemperature: fc->SetTemperature(fc->GetTemperature() + eaten * 5); break;
		case EBerrySecondaryEffect::BSE_GainTemperature: fc->SetTemperature(fc->GetTemperature() - eaten * 5); break;
		}
	}
}

void fun::EatRedBerriesAxis(float axisValue)
{
	if (axisValue > 0.1f && !ResourcesBeingEaten.Contains(EResourceType::RT_RedBerries)) ResourcesBeingEaten.Add(EResourceType::RT_RedBerries);
	if (axisValue < 0.1f && ResourcesBeingEaten.Contains(EResourceType::RT_RedBerries)) ResourcesBeingEaten.Remove(EResourceType::RT_RedBerries);
}

void fun::EatGreenBerriesAxis(float axisValue)
{
	if (axisValue > 0.1f && !ResourcesBeingEaten.Contains(EResourceType::RT_GreenBerries)) ResourcesBeingEaten.Add(EResourceType::RT_GreenBerries);
	if (axisValue < 0.1f && ResourcesBeingEaten.Contains(EResourceType::RT_GreenBerries)) ResourcesBeingEaten.Remove(EResourceType::RT_GreenBerries);
}

void fun::EatBlueBerriesAxis(float axisValue)
{
	if (axisValue > 0.1f && !ResourcesBeingEaten.Contains(EResourceType::RT_BlueBerries)) ResourcesBeingEaten.Add(EResourceType::RT_BlueBerries);
	if (axisValue < 0.1f && ResourcesBeingEaten.Contains(EResourceType::RT_BlueBerries)) ResourcesBeingEaten.Remove(EResourceType::RT_BlueBerries);
}

void fun::LightObject()
{
	if (EmberLevel <= 0.01f)
	{
		CantCreateFire();
		return;
	}

	IgniteSomething();

	FVector rayStart = FindComponentByClass<UCameraComponent>()->GetComponentLocation();
	FRotator rayDir = FindComponentByClass<UCameraComponent>()->GetComponentRotation();

	FHitResult res;

	if (GetWorld()->LineTraceSingleByChannel(res, rayStart, rayStart + rayDir.RotateVector(FVector(500, 0, 0)), ECollisionChannel::ECC_Visibility))
	{
		if (res.Actor.IsValid())
		{
			if (auto comp = res.Actor->FindComponentByClass<UFlammableComponent>())
			{
				comp->SetTemperature(500);
				UE_LOG(LogTemp, Display, TEXT("Set %s on fire"), *res.Actor->GetName());
			}
		}
	}
}

float fun::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health -= DamageAmount;

	if (Health <= 0)
	{
		OnDeath();
		Destroy();
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void fun::DropStick()
{
	Construct();

	if (!Resources.Contains(EResourceType::RT_Wood)) Resources.Add(EResourceType::RT_Wood);
	if (Resources[EResourceType::RT_Wood] >= StickCost)
	{
		Resources[EResourceType::RT_Wood] -= StickCost;

		FVector rayStart = FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		FRotator rayDir = FindComponentByClass<UCameraComponent>()->GetComponentRotation();

		FHitResult res;

		if (GetWorld()->LineTraceSingleByChannel(res, rayStart, rayStart + rayDir.RotateVector(FVector(500, 0, 0)), ECollisionChannel::ECC_Visibility))
		{
			GetWorld()->SpawnActor<AStick>(StickType, res.Location + FVector(0, 0, 70), FRotator::ZeroRotator);
		}
	}
	else
	{
		CantCreateStick();
	}
}

int32 fun::GetCountLeft(FString type)
{
	if (!Resources.Contains(EResourceType::RT_Wood)) Resources.Add(EResourceType::RT_Wood, 0);
	if (!Resources.Contains(EResourceType::RT_RedBerries)) Resources.Add(EResourceType::RT_RedBerries, 0);
	if (!Resources.Contains(EResourceType::RT_GreenBerries)) Resources.Add(EResourceType::RT_GreenBerries, 0);
	if (!Resources.Contains(EResourceType::RT_BlueBerries)) Resources.Add(EResourceType::RT_BlueBerries, 0);

	if (type == "Construct") return Resources[EResourceType::RT_Wood] / ConstructionCost;
	if (type == "Stick") return Resources[EResourceType::RT_Wood] / StickCost;
	if (type == "Ember") return EmberLevel >= 0.01f;
	if (type == "RedBerry") return Resources[EResourceType::RT_RedBerries];
	if (type == "GreenBerry") return Resources[EResourceType::RT_GreenBerries];
	if (type == "BlueBerry") return Resources[EResourceType::RT_BlueBerries];

	return -1;
}