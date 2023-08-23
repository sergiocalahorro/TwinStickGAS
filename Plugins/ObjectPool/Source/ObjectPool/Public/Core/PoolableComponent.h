// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PoolableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnabledSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisabledSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OBJECTPOOL_API UPoolableComponent : public UActorComponent
{
	GENERATED_BODY() 

#pragma region INITIALIZATION
	
public:
	
	/** Sets default values for this component's properties */
	UPoolableComponent();

#pragma endregion INITIALIZATION

#pragma region OBJECT_POOL

public:

	/** Enable object */
	UFUNCTION(BlueprintCallable)
	void Enable();

	/** Disable object */
	UFUNCTION(BlueprintCallable)
	void Disable();

	/** Retrieve enabled state for the object that owns this component */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsEnabled() const { return bIsEnabled; }

public:

	/** Delegate called when object with this component is enabled */
	UPROPERTY(BlueprintAssignable)
	FEnabledSignature EnabledDelegate;

	/** Delegate called when object with this component is disabled */
	UPROPERTY(BlueprintAssignable)
	FDisabledSignature DisabledDelegate;
	
private:

	/** Whether object with this component is enabled */
	bool bIsEnabled;

#pragma endregion OBJECT_POOL
	
};
