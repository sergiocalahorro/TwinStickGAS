// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/BlueprintFunctionLibraries/TSGAbilitySystemBlueprintLibrary.h"

// Headers - Unreal Engine
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

/** Get Instigator from attribute change data */
AActor* UTSGAbilitySystemBlueprintLibrary::GetInstigatorFromAttributeChangeData(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.GEModData != nullptr)
	{
		const FGameplayEffectContextHandle& EffectContext = ChangeData.GEModData->EffectSpec.GetEffectContext();
		return EffectContext.GetOriginalInstigator();
	}

	return nullptr;
}