// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Attributes/TSGBaseAttributeSet.h"

// Headers - TwinStickGAS
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this object's properties */
UTSGBaseAttributeSet::UTSGBaseAttributeSet()
{
	
}

#pragma endregion INITIALIZATION

#pragma region CORE

/** Get World */
UWorld* UTSGBaseAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

/** Get AbilitySystemComponent */
UTSGAbilitySystemComponent* UTSGBaseAttributeSet::GetTSGAbilitySystemComponent() const
{
	return Cast<UTSGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

#pragma endregion CORE