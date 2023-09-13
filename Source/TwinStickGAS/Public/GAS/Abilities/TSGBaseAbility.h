// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "TSGBaseAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TWINSTICKGAS_API UTSGBaseAbility : public UGameplayAbility
{
	GENERATED_BODY()

#pragma region ABILITY

public:

	/** Handle Input pressed */
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	/** Handle Input released */
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,	const FGameplayAbilityActivationInfo ActivationInfo) override;

private:

	/** Whether ability should be ended when input is released */
	UPROPERTY(EditDefaultsOnly, Category = "AA|Ability")
	bool bEndAbilityOnInputReleased = true;
	
#pragma endregion ABILITY

};
