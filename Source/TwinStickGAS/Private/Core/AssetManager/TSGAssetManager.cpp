// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/AssetManager/TSGAssetManager.h"

// Headers - Unreal Engine
#include "AbilitySystemGlobals.h"

/** Starts initial load, gets called from InitializeObjectReferences */
void UTSGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}