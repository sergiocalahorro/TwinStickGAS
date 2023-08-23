// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "TwinStickGASCharacter.generated.h"

// Forward declarations - Unreal Engine
class USpringArmComponent;
class UCameraComponent;
class UInputComponent;

// Forward declarations - TwinStickGAS
class UInputBindingComponent;

UCLASS(config=Game)
class ATwinStickGASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	/** Returns CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** Returns FollowCamera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, Category = "AA|Components")
	TObjectPtr<UCameraComponent> FollowCamera;

	/** Input component */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInputBindingComponent> InputBindingComponent;

public:
	
	ATwinStickGASCharacter();

protected:
	
	/** Allows a Pawn to set up custom input bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	/** Called when the game starts */
	virtual void BeginPlay() override;
};
