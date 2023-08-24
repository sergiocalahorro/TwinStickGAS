// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "TSGCharacter.generated.h"

// Forward declarations - Unreal Engine
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
struct FInputActionValue;

// Forward declarations - TwinStickGAS
class ATSGGameMode;
class UTSGInputBindingComponent;
class UTSGAbilitySystemComponent;
class UTSGHealthComponent;

UCLASS(config=Game)
class ATSGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

#pragma region INITIALIZATION

public:

	/** Sets default values for this actor's properties */
	ATSGCharacter();
	
#pragma endregion INITIALIZATION

	
#pragma region OVERRIDES

protected:

	/** Allow actors to initialize themselves on the C++ side after all of their components have been initialized */
	virtual void PostInitializeComponents() override;
	
	/** Called when this Pawn is possessed */
	virtual void PossessedBy(AController* NewController) override;
	
	/** Called when the game starts */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region COMPONENTS
	
private:

	/** Spring Arm */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	/** Camera */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UCameraComponent> Camera;

	/** Input binding component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGInputBindingComponent> InputBindingComponent;

	/** Ability system */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGAbilitySystemComponent> AbilitySystemComponent;

	/** Health component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGHealthComponent> HealthComponent;

#pragma endregion COMPONENTS

#pragma region REFERENCES

private:
	
	/** GameMode's reference */
	UPROPERTY()
	TObjectPtr<ATSGGameMode> GameMode;

	/** GameMode's reference */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

#pragma endregion REFERENCES

#pragma region INPUT

private:

	/** Called for movement input */
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	/** Called for aiming input */
	UFUNCTION()
	void Aim(const FInputActionValue& Value);

	/** Aiming input (Gamepad) */
	void Aim_Gamepad(const FInputActionValue& Value);

	/** Aiming input (Mouse) */
	void Aim_Mouse(const FInputActionValue& Value);

private:

	/** Last rotation saved when aiming */
	FRotator LastAimRotation;

	/** Aim input threshold when using gamepad, for affecting the character only when this threshold is surpassed */
	UPROPERTY(EditDefaultsOnly)
	float AimGamepadInputThreshold = 0.3f;

#pragma endregion INPUT

#pragma region GAS

	/** Get AbilitySystemComponent */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion GAS
	
};
