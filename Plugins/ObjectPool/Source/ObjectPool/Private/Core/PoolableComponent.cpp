// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/PoolableComponent.h"

#pragma region INITIALIZATION

/** Sets default values for this component's properties */
UPoolableComponent::UPoolableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion INITIALIZATION

#pragma region OBJECT_POOL

/** Enable object */
void UPoolableComponent::Enable()
{
	bIsEnabled = true;

	if (AActor* Owner = GetOwner())
	{
		Owner->SetActorHiddenInGame(false);
		Owner->SetActorEnableCollision(true);
	}
	
	EnabledDelegate.Broadcast();
}

/** Disable object */
void UPoolableComponent::Disable()
{
	bIsEnabled = false;

	if (AActor* Owner = GetOwner())
	{
		Owner->SetActorHiddenInGame(true);
		Owner->SetActorEnableCollision(false);
		Owner->SetActorTransform(FTransform::Identity);
		DisabledDelegate.Broadcast();
	}
}

#pragma endregion OBJECT_POOL