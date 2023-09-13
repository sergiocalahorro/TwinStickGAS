// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TSGShooterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTSGShooterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TWINSTICKGAS_API ITSGShooterInterface
{
	GENERATED_BODY()

public:

	/** Get shoot point's transform */
	virtual FTransform GetShootPointTransform() const = 0;
};
