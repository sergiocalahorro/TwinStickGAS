// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "TSGCharacter.generated.h"

// Forward declarations - Unreal Engine
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
struct FInputActionValue;

// Forward declarations - TwinStickGAS
class UTSGInputBindingComponent;

UCLASS(config=Game)
class ATSGCharacter : public ACharacter
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
	
	/** Called when the game starts */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region COMPONENTS
	
public:
	
	/** Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** Returns FollowCamera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	/** Camera boom */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Input binding component */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UTSGInputBindingComponent> InputBindingComponent;

#pragma endregion COMPONENTS

#pragma region INPUT

public:

	/** Called for movement input */
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	/** Called for aiming input */
	UFUNCTION()
	void Aim(const FInputActionValue& Value);

#pragma endregion INPUT
	
};
