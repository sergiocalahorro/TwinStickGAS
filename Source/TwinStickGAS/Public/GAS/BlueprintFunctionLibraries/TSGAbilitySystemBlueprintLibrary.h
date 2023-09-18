// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "TSGAbilitySystemBlueprintLibrary.generated.h"

// Forward declarations - TwinStickGAS
class UTSGAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGAbilitySystemBlueprintLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()

public:

	/** Get Instigator from attribute change data */
	static AActor* GetInstigatorFromAttributeChangeData(const FOnAttributeChangeData& ChangeData);

	/** Get TSGAbilitySystemComponent from Actor */
	static UTSGAbilitySystemComponent* GetTSGAbilitySystemComponent(AActor* Actor);
};
