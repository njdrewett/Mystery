// Copyright Epic Games, Inc. All Rights Reserved.

#include "MysteryGameMode.h"
#include "MysteryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMysteryGameMode::AMysteryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_Game/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
