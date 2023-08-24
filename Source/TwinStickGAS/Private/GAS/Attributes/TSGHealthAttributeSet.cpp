// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Attributes/TSGHealthAttributeSet.h"

// Headers - Unreal Engine
#include "Net/UnrealNetwork.h"

#pragma region INITIALIZATION

/** Sets default values for this object's properties */
UTSGHealthAttributeSet::UTSGHealthAttributeSet() : Health(100.f), MaxHealth(100.f)
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

#pragma endregion HEALTH
