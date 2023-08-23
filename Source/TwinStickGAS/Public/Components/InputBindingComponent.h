// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "InputBindingComponent.generated.h"

// Forward declarations - Unreal Engine
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWINSTICKGAS_API UInputBindingComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this component's properties */
	UInputBindingComponent();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES
	
protected:
	
	/** Called when the game starts */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region INPUT

public:

	/** Allows owner Pawn to set up custom input bindings */
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

protected:
	
	/** Called for movement input */
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
private:

	/** MappingContext */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputAction> LookAction;

#pragma endregion INPUT
};
