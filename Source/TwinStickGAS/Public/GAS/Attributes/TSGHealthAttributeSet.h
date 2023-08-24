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

public:

	/** Accessor for Health attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, Health);

	/** Accessor for MaxHealth attribute */
	ATTRIBUTE_ACCESSORS(UTSGHealthAttributeSet, MaxHealth);

private:

	/** Health attribute */
	UPROPERTY(BlueprintReadOnly, Category = "AA|Health", ReplicatedUsing = OnRep_Health, meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	/** MaxHealth attribute */
	UPROPERTY(BlueprintReadOnly, Category = "AA|Health", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

#pragma endregion HEALTH
	
};
