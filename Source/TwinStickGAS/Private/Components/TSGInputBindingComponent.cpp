// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TSGInputBindingComponent.h"

// Headers - Unreal Engine
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayAbilitySpec.h"

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
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem(OldController);
	if (Subsystem && InputComponent)
	{
		TeardownPlayerControls(InputComponent);
		if (InputMappingContext)
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
	
	InputComponent = nullptr;
}

/** Setup player's controls */
void UTSGInputBindingComponent::SetupPlayerControls(UEnhancedInputComponent* PlayerInputComponent)
{
	// ToDo: Abilities
	
	if (!PlayerInputComponent)
	{
		return;
	}
	
	for (auto& Action : MappedActions)
	{
		UInputAction* InputAction = Action.Key;
		FActionInputBinding& ActionInputBinding = Action.Value;
		
		switch(ActionInputBinding.ActionInputID)
		{
		case EActionInputID::Move:
			PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UTSGInputBindingComponent::InputMove_Triggered);
			break;

		case EActionInputID::Aim:
			PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UTSGInputBindingComponent::InputAim_Triggered);
			break;

		default:
			ActionInputBinding.OnPressedHandle = PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UTSGInputBindingComponent::InputAction_Pressed, InputAction).GetHandle();
			ActionInputBinding.OnReleasedHandle = PlayerInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UTSGInputBindingComponent::InputAction_Released, InputAction).GetHandle();
			break;
		}
	}
}

/** Undo player's control setup */
void UTSGInputBindingComponent::TeardownPlayerControls(UEnhancedInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		return;
	}
	
	PlayerInputComponent->ClearActionEventBindings();
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
	// ToDo: Abilities
}

/** Handle action input released event */
void UTSGInputBindingComponent::InputAction_Released(UInputAction* InputAction)
{
	// ToDo: Abilities
}

#pragma endregion INPUT
