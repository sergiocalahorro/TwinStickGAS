// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "Components/PawnComponent.h"

// Headers - TwinStickGAS
#include "General/Structs/AbilityInputBinding.h"

#include "TSGInputBindingComponent.generated.h"

// Forward declarations - Unreal Engine
class UInputMappingContext;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionValue;

// Forward declarations - TwinStickGAS
class UTSGAbilitySystemComponent;

DECLARE_DYNAMIC_DELEGATE_OneParam(FMoveTriggeredSignature, const FInputActionValue&, Value);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAimTriggeredSignature, const FInputActionValue&, Value);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWINSTICKGAS_API UTSGInputBindingComponent : public UPawnComponent
{
	GENERATED_BODY()

#pragma region OVERRIDES
	
public:

	/** Called when a component is registered */
	virtual void OnRegister() override;
	
	/** Called when a component is unregistered */
	virtual void OnUnregister() override;

#pragma endregion OVERRIDES

#pragma region CORE

protected:

	/** Called when pawn restarts, bound to dynamic delegate */
	UFUNCTION()
	virtual void OnPawnRestarted(APawn* Pawn);

	/** Called when pawn restarts, bound to dynamic delegate */
	UFUNCTION()
	virtual void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

#pragma endregion CORE

#pragma region INPUT

private:

	/** Setup custom input bindings for incoming pawn */
	void SetupInputComponent(APawn* Pawn);

	/** Release input component from old controller */
	void ReleaseInputComponent(AController* OldController = nullptr);

	/** Reset input bindings */
	void ResetBindings();

	/** Setup player's controls */
	void SetupPlayerControls(UEnhancedInputComponent* PlayerInputComponent);

	/** Get enhanced input subsystem */
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem(AController* OldController = nullptr) const;

	/** Handle move input triggered event */
	void InputMove_Triggered(const FInputActionValue& Value);

	/** Handle aim input triggered event */
	void InputAim_Triggered(const FInputActionValue& Value);

	/** Handle action input pressed event */
	void InputAction_Pressed(UInputAction* InputAction);

	/** Handle action input released event */
	void InputAction_Released(UInputAction* InputAction);

public:

	/** Delegate called when move input is triggered */
	FMoveTriggeredSignature MoveTriggeredDelegate;

	/** Delegate called when aim input is triggered */
	FAimTriggeredSignature AimTriggeredDelegate;
	
private:

	/** Default Input Mapping Context */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	/** Move Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputAction> InputActionMove;

	/** Aim Input Action */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TObjectPtr<UInputAction> InputActionAim;

	/** Mapped abilities */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Input")
	TMap<TObjectPtr<UInputAction>, FAbilityInputBinding> MappedAbilities;

	/** Input component that is currently bound */
	UPROPERTY(transient)
	TObjectPtr<UEnhancedInputComponent> InputComponent;

#pragma endregion INPUT

#pragma region GAS

public:

	/** Setup ability system */
	void SetupAbilitySystem();

private:

	/** Ability system component */
	UPROPERTY(transient)
	TObjectPtr<UTSGAbilitySystemComponent> AbilitySystemComponent;
	
#pragma endregion GAS
};
