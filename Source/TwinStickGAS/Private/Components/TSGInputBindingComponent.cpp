// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TSGInputBindingComponent.h"

// Headers - Unreal Engine
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayAbilitySpec.h"

// Headers - TwinStickGAS
#include "GAS/Abilities/TSGBaseAbility.h"
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"

#pragma region OVERRIDES

/** Called when a component is registered */
void UTSGInputBindingComponent::OnRegister()
{
	Super::OnRegister();
	
	if (const UWorld* World = GetWorld()) 
	{
		if (World->IsGameWorld())
		{
			if (APawn* PawnOwner = GetPawn<APawn>())
			{
				PawnOwner->ReceiveRestartedDelegate.AddDynamic(this, &UTSGInputBindingComponent::OnPawnRestarted);
				PawnOwner->ReceiveControllerChangedDelegate.AddDynamic(this, &UTSGInputBindingComponent::OnControllerChanged);

				// If pawn has an input component, it was added after restart
				if (PawnOwner->InputComponent)
				{
					OnPawnRestarted(PawnOwner);
				}
			}
		}
	}
}
	
/** Called when a component is unregistered */
void UTSGInputBindingComponent::OnUnregister()
{
	if (const UWorld* World = GetWorld())
	{
		if (World->IsGameWorld())
		{
			ReleaseInputComponent();
			if (APawn* PawnOwner = GetPawn<APawn>())
			{
				PawnOwner->ReceiveRestartedDelegate.RemoveAll(this);
				PawnOwner->ReceiveControllerChangedDelegate.RemoveAll(this);
			}
		}
	}

	Super::OnUnregister();
}

#pragma endregion OVERRIDES

#pragma region CORE

/** Called when pawn restarts, bound to dynamic delegate */
void UTSGInputBindingComponent::OnPawnRestarted(APawn* Pawn)
{
	if (Pawn && Pawn == GetOwner() && Pawn->InputComponent)
	{
		ReleaseInputComponent();
		if (Pawn->InputComponent)
		{
			SetupInputComponent(Pawn);
		}
	}
}

/** Called when pawn restarts, bound to dynamic delegate */
void UTSGInputBindingComponent::OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	if (Pawn && Pawn == GetOwner() && OldController)
	{
		ReleaseInputComponent(OldController);
	}
}

#pragma endregion CORE

#pragma region INPUT

/** Setup custom input bindings for incoming pawn */
void UTSGInputBindingComponent::SetupInputComponent(APawn* Pawn)
{
	InputComponent = CastChecked<UEnhancedInputComponent>(Pawn->InputComponent);
	if (InputComponent)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
		check(Subsystem);

		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		SetupPlayerControls(InputComponent);
	}
}

/** Release input component from old controller */
void UTSGInputBindingComponent::ReleaseInputComponent(AController* OldController)
{
	ResetBindings();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem(OldController);
	if (Subsystem && InputComponent)
	{
		if (InputMappingContext)
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
	
	InputComponent = nullptr;
}

/** Reset input bindings */
void UTSGInputBindingComponent::ResetBindings()
{
	if (InputComponent)
	{
		InputComponent->ClearActionBindings();
	}
	
	for (auto& InputAbility : MappedAbilities)
	{
		if (AbilitySystemComponent)
		{
			const int32 ExpectedInputID = static_cast<int32>(InputAbility.Value.InputID);
			for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : InputAbility.Value.BoundAbilitiesStack)
			{
				FGameplayAbilitySpec* FoundAbility = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandle);
				if (FoundAbility && FoundAbility->InputID == ExpectedInputID)
				{
					FoundAbility->InputID = static_cast<int32>(EAbilityInputID::NONE);
				}
			}
		}
	}

	AbilitySystemComponent = nullptr;
}

/** Setup player's controls */
void UTSGInputBindingComponent::SetupPlayerControls(UEnhancedInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		return;
	}

	ResetBindings();

	PlayerInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &UTSGInputBindingComponent::InputMove_Triggered);
	PlayerInputComponent->BindAction(InputActionAim, ETriggerEvent::Triggered, this, &UTSGInputBindingComponent::InputAim_Triggered);
	
	SetupAbilitySystem();
	
	for (auto& InputAbility : MappedAbilities)
	{
		if (UInputAction* InputAction = InputAbility.Key)
		{
			if (FAbilityInputBinding* AbilityInputBinding = &InputAbility.Value)
			{
				AbilityInputBinding->OnPressedHandle = PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UTSGInputBindingComponent::InputAction_Pressed, InputAction).GetHandle();
				AbilityInputBinding->OnReleasedHandle = PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UTSGInputBindingComponent::InputAction_Released, InputAction).GetHandle();
				
				const FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GrantAbility(AbilityInputBinding->AbilityClass, AbilityInputBinding->Level, static_cast<int32>(AbilityInputBinding->InputID));
				if (FGameplayAbilitySpec* FoundAbility = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandle))
				{
					FoundAbility->InputID = static_cast<int32>(AbilityInputBinding->InputID);
				}
			}
		}
	}
}

/** Get enhanced input subsystem */
UEnhancedInputLocalPlayerSubsystem* UTSGInputBindingComponent::GetEnhancedInputSubsystem(AController* OldController) const
{
	const APlayerController* PlayerController = GetController<APlayerController>();
	if (!PlayerController)
	{
		PlayerController = Cast<APlayerController>(OldController);
	}

	if (PlayerController)
	{
		if (const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			return LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		}
	}

	return nullptr;
}

/** Handle move input triggered event */
void UTSGInputBindingComponent::InputMove_Triggered(const FInputActionValue& Value)
{
	MoveTriggeredDelegate.Execute(Value);
}

/** Handle aim input triggered event */
void UTSGInputBindingComponent::InputAim_Triggered(const FInputActionValue& Value)
{
	AimTriggeredDelegate.Execute(Value);
}

/** Handle action input pressed event */
void UTSGInputBindingComponent::InputAction_Pressed(UInputAction* InputAction)
{
	if (!AbilitySystemComponent)
	{
		SetupAbilitySystem();
	}

	check(AbilitySystemComponent);
	
	if (FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction))
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(AbilityInputBinding->InputID));
	}
}

/** Handle action input released event */
void UTSGInputBindingComponent::InputAction_Released(UInputAction* InputAction)
{
	check(AbilitySystemComponent);
	
	if (FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction))
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(AbilityInputBinding->InputID));
	}
}

#pragma endregion INPUT

#pragma region GAS

/** Setup ability system */
void UTSGInputBindingComponent::SetupAbilitySystem()
{
	const AActor* ComponentOwner = GetOwner();
	check(ComponentOwner);

	AbilitySystemComponent = CastChecked<UTSGAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ComponentOwner));
}

#pragma endregion GAS
