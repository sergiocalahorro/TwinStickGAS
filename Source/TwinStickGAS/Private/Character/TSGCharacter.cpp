// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/TSGCharacter.h"

// Headers - Unreal Engine
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

// Headers - TwinStickGAS
#include "Components/TSGHealthComponent.h"
#include "Components/TSGInputBindingComponent.h"
#include "GameMode/TSGGameMode.h"
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this actor's properties */
ATSGCharacter::ATSGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 900.f;
	SpringArm->bDoCollisionTest = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Input binding
	InputBindingComponent = CreateDefaultSubobject<UTSGInputBindingComponent>(TEXT("InputBindingComponent"));

	// Ability system
	AbilitySystemComponent = CreateDefaultSubobject<UTSGAbilitySystemComponent>(TEXT("AbilitySytemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	HealthComponent = CreateDefaultSubobject<UTSGHealthComponent>(TEXT("HealthComponent"));
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized */
void ATSGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	InputBindingComponent->MoveTriggeredDelegate.BindDynamic(this, &ATSGCharacter::Move);
	InputBindingComponent->AimTriggeredDelegate.BindDynamic(this, &ATSGCharacter::Aim);

	HealthComponent->InitializeWithAbilitySystem(AbilitySystemComponent);
}

/** Called when this Pawn is possessed */
void ATSGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	PlayerController = CastChecked<APlayerController>(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}

/** Called when the game starts */
void ATSGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ATSGGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

#pragma endregion OVERRIDES

#pragma region INPUT

/** Called for movement input */
void ATSGCharacter::Move(const FInputActionValue& Value)
{
	// Find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// Get forward and right vectors
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Add movement
	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

/** Called for aiming input */
void ATSGCharacter::Aim(const FInputActionValue& Value)
{
	if (!GameMode)
	{
		return;
	}
	
	if (GameMode->IsUsingGamepad())
	{
		Aim_Gamepad(Value);
	}
	else
	{
		Aim_Mouse(Value);
	}
}

/** Aiming input (Gamepad) */
void ATSGCharacter::Aim_Gamepad(const FInputActionValue& Value)
{
	const FVector2D AimVector = Value.Get<FVector2D>();
	const FVector LocalAimInputDirection = FVector(-AimVector.Y, AimVector.X, 0.f).GetClampedToMaxSize(1.0f);
	const float AimInputAmount = LocalAimInputDirection.Size2D();
	
	// Use current input direction's rotation, or last one if threshold isn't reached
	if (AimInputAmount >= AimGamepadInputThreshold)
	{
		const FRotator YawControlRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		const FVector WorldAimInputDirection = YawControlRotation.RotateVector(LocalAimInputDirection).GetSafeNormal();
		const FRotator AimRotation = FRotator(0.f, WorldAimInputDirection.Rotation().Yaw, 0.f);
		SetActorRotation(AimRotation);
		LastAimRotation = AimRotation;
	}
	else
	{
		SetActorRotation(LastAimRotation);
	}
}

/** Aiming input (Mouse) */
void ATSGCharacter::Aim_Mouse(const FInputActionValue& Value)
{
	if (!PlayerController)
	{
		return;
	}

	// Use current mouse input direction's rotation, or last one if location couldn't be found
	FHitResult OutHit;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, OutHit))
	{
		// ToDo: As PlayerController->SetShowMouseCursor() actually affects the input, replace this later by displaying the mouse cursor using UI/Decal
		DrawDebugSphere(GetWorld(), OutHit.Location, 16.f, 16, FColor::Red);
		
		const FVector WorldAimInputDirection = (OutHit.Location - GetActorLocation()).GetSafeNormal2D();
		const FRotator AimRotation = FRotator(0.f, WorldAimInputDirection.Rotation().Yaw, 0.f);
		SetActorRotation(AimRotation);
		LastAimRotation = AimRotation;
	}
	else
	{
		SetActorRotation(LastAimRotation);
	}
}

#pragma endregion INPUT

#pragma region GAS

/** Get AbilitySystemComponent */
UAbilitySystemComponent* ATSGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

#pragma endregion GAS