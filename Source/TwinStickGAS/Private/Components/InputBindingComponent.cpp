// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputBindingComponent.h"

// Headers - Unreal Engine
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

#pragma region INITIALIZATION

/** Sets default values for this component's properties */
UInputBindingComponent::UInputBindingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Called when the game starts */
void UInputBindingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	const APawn* Pawn = CastChecked<APawn>(GetOwner());
	
	if (AController* Controller = Pawn->GetController())
	{
		if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

#pragma endregion OVERRIDES

#pragma region INPUT

/** Allows owner Pawn to set up custom input bindings */
void UInputBindingComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		ACharacter* Character = CastChecked<ACharacter>(GetOwner());
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, Character, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, Character, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UInputBindingComponent::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &UInputBindingComponent::Look);
	}
}

/** Called for movement input */
void UInputBindingComponent::Move(const FInputActionValue& Value)
{
	APawn* Pawn = CastChecked<APawn>(GetOwner());
	
	if (const AController* Controller = Pawn->GetController())
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward and right vectors
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement
		const FVector2D MovementVector = Value.Get<FVector2D>();
		Pawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		Pawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

/** Called for looking input */
void UInputBindingComponent::Look(const FInputActionValue& Value)
{
	APawn* Pawn = CastChecked<APawn>(GetOwner());

	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	Pawn->AddControllerYawInput(LookAxisVector.X);
	Pawn->AddControllerPitchInput(LookAxisVector.Y);
}

#pragma endregion INPUT
