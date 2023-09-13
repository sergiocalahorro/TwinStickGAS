// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Abilities/TSGBaseAbility.h"

/** Handle Input pressed */
void UTSGBaseAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);	
}

/** Handle Input released */
void UTSGBaseAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (bEndAbilityOnInputReleased)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
	
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);	
}