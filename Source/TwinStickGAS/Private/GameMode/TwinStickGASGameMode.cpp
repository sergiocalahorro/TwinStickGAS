// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/TwinStickGASGameMode.h"
#include "Character/TwinStickGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATwinStickGASGameMode::ATwinStickGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
