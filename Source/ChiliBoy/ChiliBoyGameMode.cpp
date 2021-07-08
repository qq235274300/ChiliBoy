// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChiliBoyGameMode.h"
#include "ChiliBoyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AChiliBoyGameMode::AChiliBoyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
