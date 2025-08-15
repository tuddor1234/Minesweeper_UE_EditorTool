// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoTechMinesweeperCommands.h"

#define LOCTEXT_NAMESPACE "FGeoTechMinesweeperModule"

void FGeoTechMinesweeperCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "GeoTechMinesweeper", "Bring up GeoTechMinesweeper window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
