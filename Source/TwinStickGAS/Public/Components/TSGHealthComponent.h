// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "TSGHealthComponent.generated.h"

// Forward declarations - Unreal Engine
struct FOnAttributeChangeData;

// Forward declarations - TwinStickGAS
class UTSGAbilitySystemComponent;
class UTSGHealthAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FLyraHealthAttributeChangedSignature, UTSGHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWINSTICKGAS_API UTSGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this component's properties */
	UTSGHealthComponent();

#pragma region INITIALIZATION

#pragma region HEALTH

public:

	/** Initialize attribute with incoming ability system */
	void InitializeWithAbilitySystem(UTSGAbilitySystemComponent* InASC);

private:

	/** Handle changes in Health attribute */
	void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);

	/** Handle changes in MaxHealth attribute */
	void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);

public:

	/** Delegate called when Health attribute is changed */
	FLyraHealthAttributeChangedSignature HealthChangedDelegate;

	/** Delegate called when MaxHealth attribute is changed */
	FLyraHealthAttributeChangedSignature MaxHealthChangedDelegate;

private:

	/** Ability system */
	UPROPERTY()
	TObjectPtr<UTSGAbilitySystemComponent> AbilitySystemComponent;

	/** Health attribute */
	UPROPERTY()
	TObjectPtr<const UTSGHealthAttributeSet> HealthAttributeSet;

#pragma endregion HEALTH	
	
};
