// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "GeoTechMinesweeperStyle.h"

class FGeoTechMinesweeperCommands : public TCommands<FGeoTechMinesweeperCommands>
{
public:

	FGeoTechMinesweeperCommands()
		: TCommands<FGeoTechMinesweeperCommands>(TEXT("GeoTechMinesweeper"), NSLOCTEXT("Contexts", "GeoTechMinesweeper", "GeoTechMinesweeper Plugin"), NAME_None, FGeoTechMinesweeperStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};