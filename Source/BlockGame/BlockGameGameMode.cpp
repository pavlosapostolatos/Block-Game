// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlockGameGameMode.h"
#include "BlockGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlockGameGameMode::ABlockGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
