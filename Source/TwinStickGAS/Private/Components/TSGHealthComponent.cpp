// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TSGHealthComponent.h"

// Headers - TwinStickGAS
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"
#include "GAS/Attributes/TSGHealthAttributeSet.h"
#include "GAS/BlueprintFunctionLibraries/TSGAbilitySystemBlueprintLibrary.h"

#pragma region INITIALIZATION

/** Sets default values for this component's properties */
UTSGHealthComponent::UTSGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion INITIALIZATION

#pragma region HEALTH

/** Initialize attribute with incoming ability system */
void UTSGHealthComponent::InitializeWithAbilitySystem(UTSGAbilitySystemComponent* InASC)
{
	if (AbilitySystemComponent || !InASC)
	{
		return;
	}

	AbilitySystemComponent = InASC;
	
	HealthAttributeSet = AbilitySystemComponent->GetSet<UTSGHealthAttributeSet>();
	if (!HealthAttributeSet)
	{
		return;
	}

	// Register to listen for attribute changes.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTSGHealthAttributeSet::GetHealthAttribute()).AddUObject(this, &UTSGHealthComponent::HandleHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTSGHealthAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UTSGHealthComponent::HandleMaxHealthChanged);

	AbilitySystemComponent->SetNumericAttributeBase(UTSGHealthAttributeSet::GetHealthAttribute(), HealthAttributeSet->GetMaxHealth());
	
	HealthChangedDelegate.Broadcast(this, HealthAttributeSet->GetHealth(), HealthAttributeSet->GetHealth(), nullptr);
	MaxHealthChangedDelegate.Broadcast(this, HealthAttributeSet->GetHealth(), HealthAttributeSet->GetHealth(), nullptr);
}

/** Handle changes in Health attribute */
void UTSGHealthComponent::HandleHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	HealthChangedDelegate.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, UTSGAbilitySystemBlueprintLibrary::GetInstigatorFromAttributeChangeData(ChangeData));
}

/** Handle changes in MaxHealth attribute */
void UTSGHealthComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	MaxHealthChangedDelegate.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, UTSGAbilitySystemBlueprintLibrary::GetInstigatorFromAttributeChangeData(ChangeData));
}

#pragma endregion HEALTH