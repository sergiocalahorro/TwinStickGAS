// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "TSGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKGAS_API UTSGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;
};
