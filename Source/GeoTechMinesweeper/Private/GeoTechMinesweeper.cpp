// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoTechMinesweeper.h"
#include "GeoTechMinesweeperStyle.h"
#include "GeoTechMinesweeperCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName GeoTechMinesweeperTabName("GeoTechMinesweeper");

#define LOCTEXT_NAMESPACE "FGeoTechMinesweeperModule"

void FGeoTechMinesweeperModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGeoTechMinesweeperStyle::Initialize();
	FGeoTechMinesweeperStyle::ReloadTextures();

	FGeoTechMinesweeperCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGeoTechMinesweeperCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FGeoTechMinesweeperModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGeoTechMinesweeperModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(GeoTechMinesweeperTabName, FOnSpawnTab::CreateRaw(this, &FGeoTechMinesweeperModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FGeoTechMinesweeperTabTitle", "GeoTechMinesweeper"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FGeoTechMinesweeperModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGeoTechMinesweeperStyle::Shutdown();

	FGeoTechMinesweeperCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(GeoTechMinesweeperTabName);
}

TSharedRef<SDockTab> FGeoTechMinesweeperModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FGeoTechMinesweeperModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("GeoTechMinesweeper.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			m_Game.GetGUI()
		];
}

void FGeoTechMinesweeperModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(GeoTechMinesweeperTabName);
}

void FGeoTechMinesweeperModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGeoTechMinesweeperCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGeoTechMinesweeperCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGeoTechMinesweeperModule, GeoTechMinesweeper)