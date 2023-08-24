// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "TSGAbilitySystemComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWINSTICKGAS_API UTSGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	/** Sets default values for this component's properties */
	UTSGAbilitySystemComponent();

};
