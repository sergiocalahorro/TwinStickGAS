// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"

// Headers - TwinStickGAS
#include "TSGBaseAttributeSet.h"

#include "TSGHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGHealthAttributeSet : public UTSGBaseAttributeSet
{
	GENERATED_BODY()

#pragma region INITIALIZATION

public:

	/** Sets default values for this object's properties */
	UTSGHealthAttributeSet();

#pragma endregion INITIALIZATION

#pragma region OVERRIDES

public:

	/** Returns the properties used for network replication */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma endregion OVERRIDES

#pragma region HEALTH

public:

	/** RepNotify for Health */
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	/** RepNotify for MaxHealth */
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	/** Called just before modifying the value of an attribute. AttributeSet can make additional modifications here. Return true to continue, or false to throw out the modification */	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	/** Called just before a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** Called just before any modification happens to an attribute */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	/** Called just after any modification happens to an attribute */
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	/** This is called just before any modification happens to an attribute's base value when an attribute aggregator exists */
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	/** Called just after any modification happens to an attribute's base value when an attribute aggregator exists */
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	/** Clamp the value of an attribute */
	void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;

	/** Accessor for Health attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, Health);

	/** Accessor for MaxHealth attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, MaxHealth);

	/** Accessor for Healing meta attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, Healing);

	/** Accessor for Damage meta attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, Damage)
	
private:

	/** Health attribute */
	UPROPERTY(BlueprintReadOnly, Category = "AA|Health", ReplicatedUsing = OnRep_Health, meta = (AllowPrivateAccess = true)) // HideFromModifiers
	FGameplayAttributeData Health;

	/** MaxHealth attribute */
	UPROPERTY(BlueprintReadOnly, Category = "AA|Health", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	/** Meta attribute: Incoming healing. This is mapped directly to +Health */
	UPROPERTY(BlueprintReadOnly, Category="AA|Health", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Healing;

	/** Meta attribute: Incoming damage. This is mapped directly to -Health */
	UPROPERTY(BlueprintReadOnly, Category="AA|Health", meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	/** Used to track when the health reaches zero */
	bool bOutOfHealth;

	/** Delegate to broadcast when the Health attribute reaches zero */
	FAttributeEvent OutOfHealthDelegate;

#pragma endregion HEALTH
	
};
