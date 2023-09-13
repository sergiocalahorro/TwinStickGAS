// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "General/Interfaces/TSGShooterInterface.h"

#include "TSGCharacter.generated.h"

// Forward declarations - Unreal Engine
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
struct FInputActionValue;
struct FGameplayAbilitySpecHandle;

// Forward declarations - TwinStickGAS
class ATSGGameMode;
class UTSGInputBindingComponent;
class UTSGAbilitySystemComponent;
class UTSGHealthComponent;
class UTSGBaseAbility;
class UObjectPoolComponent;

UCLASS(config=Game, Abstract, Blueprintable)
class ATSGCharacter : public ACharacter, public IAbilitySystemInterface, public ITSGShooterInterface
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

	/** ShootPoint */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<USceneComponent> ShootPoint;

	/** Input binding component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGInputBindingComponent> InputBindingComponent;

	/** Ability system */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGAbilitySystemComponent> AbilitySystemComponent;

	/** Health component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGHealthComponent> HealthComponent;

	/** Object pool component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UObjectPoolComponent> ObjectPoolComponent;

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
	UPROPERTY(EditDefaultsOnly, Category = " AA|Input")
	float AimGamepadInputThreshold = 0.3f;

#pragma endregion INPUT

#pragma region GAS

	/** Get AbilitySystemComponent */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

#pragma endregion GAS

#pragma region SHOOTER

public:

	/** Get shoot point's transform */
	FTransform GetShootPointTransform() const override;

#pragma endregion SHOOTER
	
};
