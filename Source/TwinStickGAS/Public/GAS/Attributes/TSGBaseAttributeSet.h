// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "TSGBaseAttributeSet.generated.h"

// Forward declarations - TwinStickGAS
class UTSGAbilitySystemComponent;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_FourParams(FAttributeEvent, AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec& EffectSpec, float EffectMagnitude);

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:

	/** Sets default values for this object's properties */
	UTSGBaseAttributeSet();

#pragma endregion INITIALIZATION

#pragma region CORE

public:

	/** Get World */
	UWorld* GetWorld() const override;

	/** Get AbilitySystemComponent */
	UTSGAbilitySystemComponent* GetTSGAbilitySystemComponent() const;

#pragma endregion CORE
	
};
