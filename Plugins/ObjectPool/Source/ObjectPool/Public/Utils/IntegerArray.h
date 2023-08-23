// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IntegerArray.generated.h"

USTRUCT(BlueprintType)
struct FIntegerArray
{
	GENERATED_BODY()

public:

	/** Default Constructor */
	FIntegerArray()
	{
		
	}

	/** Constructor */
	FIntegerArray(const TArray<int32>& InIntegers) : Integers(InIntegers)
	{
		
	}
	
public:

	/** Array of integers */
	UPROPERTY()
	TArray<int32> Integers;
};
