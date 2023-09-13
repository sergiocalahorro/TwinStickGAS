// Fill out your copyright notice in the Description page of Project Settings.

#include "General/BlueprintFunctionLibraries/TSGGameplayStatics.h"

// Headers - TwinStickGAS
#include "Core/ObjectPoolComponent.h"

/** Spawn object from pool */
AActor* UTSGGameplayStatics::SpawnPoolableObject(AActor* Instigator, TSubclassOf<AActor> PoolableObjectClass, const FTransform& SpawnTransform)
{
	if (!Instigator || !PoolableObjectClass)
	{
		return nullptr;
	}

	UObjectPoolComponent* ObjectPool = Instigator->FindComponentByClass<UObjectPoolComponent>();
	if (!ObjectPool)
	{
		return nullptr;
	}

	return ObjectPool->GetPooledObject(PoolableObjectClass, SpawnTransform);
}