// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"

// Headers - TwinStickGAS
#include "General/Enums/ActionInputID.h"

#include "ActionInputBinding.generated.h"


USTRUCT()
struct FActionInputBinding
{
	GENERATED_BODY()

	/** Action Input ID */
	UPROPERTY(EditDefaultsOnly)
	EActionInputID ActionInputID = EActionInputID::NONE;

	/** Handle when input is pressed */
	uint32 OnPressedHandle = 0;

	/** Handle when input is released */
	uint32 OnReleasedHandle = 0;

	/** Bound abilities */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};
