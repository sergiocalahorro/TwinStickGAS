// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "TSGGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()

public:

	/** Spawn object from pool */
	static AActor* SpawnPoolableObject(AActor* Instigator, TSubclassOf<AActor> PoolableObjectClass, const FTransform& SpawnTransform);
};
