// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActorArray.generated.h"

USTRUCT(BlueprintType)
struct FActorArray
{
	GENERATED_BODY()

	/** Default Constructor */
	FActorArray()
	{
		
	}
	
	/** Constructor */
	FActorArray(const TArray<TObjectPtr<AActor>>& InActors) : Actors(InActors)
	{
		
	}
	
public:

	/** Array of AActor */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> Actors;
};
