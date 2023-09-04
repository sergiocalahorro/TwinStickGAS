// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"

// Headers - TwinStickGAS
#include "General/Enums/AbilityInputID.h"

#include "AbilityInputBinding.generated.h"

// Forward declarations - TwinStickGAS
class UTSGBaseAbility;

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	/** Ability class */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTSGBaseAbility> AbilityClass;

	/** Ability level */
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 1, UIMin = 1))
	int32 Level = 1;

	/** Ability input ID */
	UPROPERTY(EditDefaultsOnly)
	EAbilityInputID InputID = EAbilityInputID::NONE;

	/** Handle when input is pressed */
	uint32 OnPressedHandle = 0;

	/** Handle when input is released */
	uint32 OnReleasedHandle = 0;

	/** Bound abilities */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};
