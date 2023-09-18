// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Attributes/TSGHealthAttributeSet.h"

// Headers - Unreal Engine
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

// Headers - TwinStickGAS
#include "GAS/AbilitySystem/TSGAbilitySystemComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this object's properties */
UTSGHealthAttributeSet::UTSGHealthAttributeSet() : Health(100.f), MaxHealth(100.f), bOutOfHealth(false)
{
	
}

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

/** Returns the properties used for network replication */
void UTSGHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSGHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSGHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

#pragma endregion OVERRIDES

#pragma region HEALTH

/** RepNotify for Health */
void UTSGHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSGHealthAttributeSet, Health, OldHealth);
}

/** RepNotify for MaxHealth */
void UTSGHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSGHealthAttributeSet, Health, MaxHealth);
}

/** Called just before modifying the value of an attribute. AttributeSet can make additional modifications here. Return true to continue, or false to throw out the modification */	
bool UTSGHealthAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

/** Called just before a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made */
void UTSGHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0.f, GetMaxHealth()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() + GetHealing(), 0.f, GetMaxHealth()));
		SetHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if ((GetHealth() <= 0.0f) && !bOutOfHealth)
	{
		const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
		AActor* Instigator = EffectContext.GetOriginalInstigator();
		AActor* Causer = EffectContext.GetEffectCauser();

		OutOfHealthDelegate.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
	}

	bOutOfHealth = (GetHealth() <= 0.0f);
}

/** Called just before any modification happens to an attribute */
void UTSGHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttributeOnChange(Attribute, NewValue);
}

/** Called just after any modification happens to an attribute */
void UTSGHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		// Make sure current health is not greater than the new max health.
		if (GetHealth() > NewValue)
		{
			UTSGAbilitySystemComponent* AbilitySystemComponent = GetTSGAbilitySystemComponent();
			check(AbilitySystemComponent);

			AbilitySystemComponent->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}

	if (bOutOfHealth && (GetHealth() > 0.0f))
	{
		bOutOfHealth = false;
	}
}

/** This is called just before any modification happens to an attribute's base value when an attribute aggregator exists */
void UTSGHealthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const 
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttributeOnChange(Attribute, NewValue);
}

/** Called just after any modification happens to an attribute's base value when an attribute aggregator exists */
void UTSGHealthAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const 
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

/** Clamp the value of an attribute */
void UTSGHealthAttributeSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
}

#pragma endregion HEALTH
