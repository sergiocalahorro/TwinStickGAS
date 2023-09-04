// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "TSGAbilitySystemComponent.generated.h"

// Forward declarations - TwinStickGAS
class UTSGBaseAbility;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWINSTICKGAS_API UTSGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this component's properties */
	UTSGAbilitySystemComponent();

#pragma endregion INITIALIZATION

#pragma region ABILITIES

public:

	/** Grant ability to the owner of this ability system */
	FGameplayAbilitySpecHandle GrantAbility(const TSubclassOf<UTSGBaseAbility>& Ability, int32 Level, int32 InputID);

#pragma endregion ABILITIES

};
