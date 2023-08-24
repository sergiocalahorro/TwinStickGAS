// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CommonInputBaseTypes.h"

#include "TSGGameMode.generated.h"

// Forward declarations - Unreal Engine
class UCommonInputSubsystem;

UCLASS(minimalapi)
class ATSGGameMode : public AGameModeBase
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:

	/** Constructor */
	ATSGGameMode();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

protected:

	/** Called when game starts */
	virtual void BeginPlay() override;

#pragma endregion OVERRIDES

#pragma region CORE

public:

	/** Getter of CommonInputSubsystem */
	FORCEINLINE UCommonInputSubsystem* GetCommonInputSubsystem() const { return CommonInputSubsystem; }

	/** Getter of bIsUsingGamepad */
	FORCEINLINE bool IsUsingGamepad() const { return bIsUsingGamepad; }

private:
	
	/** Function called when Input Method is changed */
	void UpdateInputMethod(ECommonInputType NewInputType);

	/** Setup delegates' bindings */
	void SetupBindings();

private:

	/** PlayerController's reference */
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

	/** CommonInput Subsystem */
	UPROPERTY()
	TObjectPtr<UCommonInputSubsystem> CommonInputSubsystem;

	/** Whether player is using gamepad or mouse and keyboard */
	bool bIsUsingGamepad;

#pragma endregion CORE
	
};
