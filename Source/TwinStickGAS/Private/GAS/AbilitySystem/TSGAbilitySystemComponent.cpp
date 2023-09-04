// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"

// Headers - TwinStickGAS
#include "GAS/Abilities/TSGBaseAbility.h"
#include "General/Enums/AbilityInputID.h"

#pragma region INITIALIZATION

/** Sets default values for this component's properties */
UTSGAbilitySystemComponent::UTSGAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion INITIALIZATION

#pragma region ABILITIES

/** Grant ability to the owner of this ability system */
FGameplayAbilitySpecHandle UTSGAbilitySystemComponent::GrantAbility(const TSubclassOf<UTSGBaseAbility>& Ability, int32 Level, int32 InputID)
{
	const FGameplayAbilitySpec AbilitySpec(Ability, Level, InputID, GetOwner());
	const FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);

	return AbilitySpecHandle;
}

#pragma endregion ABILITIES