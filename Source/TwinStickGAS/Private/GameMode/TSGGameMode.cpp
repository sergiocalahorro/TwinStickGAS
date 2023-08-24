// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TSGGameMode.h"

// Headers - Unreal Engine
#include "CommonInputSubsystem.h"
#include "Kismet/GameplayStatics.h"

#pragma region INITIALIZATION

/** Constructor */
ATSGGameMode::ATSGGameMode()
{
	
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Called when game starts */
void ATSGGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		CommonInputSubsystem = UCommonInputSubsystem::Get(PlayerController->GetLocalPlayer());
		UpdateInputMethod(CommonInputSubsystem->GetCurrentInputType());
	}

	SetupBindings();
}
	
#pragma endregion OVERRIDES

#pragma region CORE

/** Setup delegates' bindings */
void ATSGGameMode::SetupBindings()
{
	if (CommonInputSubsystem)
	{
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &ATSGGameMode::UpdateInputMethod);
	}
}

/** Function called when Input Method is changed */
void ATSGGameMode::UpdateInputMethod(ECommonInputType NewInputType)
{
	if (!PlayerController)
	{
		return;
	}
	
	bIsUsingGamepad = NewInputType == ECommonInputType::Gamepad;
}

#pragma endregion CORE
