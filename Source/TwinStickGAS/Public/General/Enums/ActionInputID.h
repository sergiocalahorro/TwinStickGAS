// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Headers - Unreal Engine
#include "CoreMinimal.h"

#include "ActionInputID.generated.h"


UENUM()
enum class EActionInputID : uint8
{
	NONE,
	Move,
	Aim,
	Shoot
};
