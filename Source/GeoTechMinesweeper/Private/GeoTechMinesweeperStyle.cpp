// Copyright Epic Games, Inc. All Rights Reserved.

#include "GeoTechMinesweeperStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FGeoTechMinesweeperStyle::StyleInstance = nullptr;

void FGeoTechMinesweeperStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGeoTechMinesweeperStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGeoTechMinesweeperStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GeoTechMinesweeperStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FGeoTechMinesweeperStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GeoTechMinesweeperStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GeoTechMinesweeper")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GeoTechMinesweeper.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("Mine"), Icon20x20));
	Style->Set("GTM.Mine", new IMAGE_BRUSH_SVG(TEXT("Mine"), Icon20x20));
	Style->Set("GTM.Default", new IMAGE_BRUSH_SVG(TEXT("Default"), Icon20x20));
	Style->Set("GTM.0", new IMAGE_BRUSH_SVG(TEXT("Clicked"), Icon20x20));
	Style->Set("GTM.1", new IMAGE_BRUSH_SVG(TEXT("1"), Icon20x20));
	Style->Set("GTM.2", new IMAGE_BRUSH_SVG(TEXT("2"), Icon20x20));
	Style->Set("GTM.3", new IMAGE_BRUSH_SVG(TEXT("3"), Icon20x20));
	Style->Set("GTM.4", new IMAGE_BRUSH_SVG(TEXT("4"), Icon20x20));
	Style->Set("GTM.5", new IMAGE_BRUSH_SVG(TEXT("5"), Icon20x20));
	Style->Set("GTM.6", new IMAGE_BRUSH_SVG(TEXT("6"), Icon20x20));
	Style->Set("GTM.7", new IMAGE_BRUSH_SVG(TEXT("7"), Icon20x20));
	Style->Set("GTM.8", new IMAGE_BRUSH_SVG(TEXT("8"), Icon20x20));
	

	return Style;
}

void FGeoTechMinesweeperStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGeoTechMinesweeperStyle::Get()
{
	return *StyleInstance;
}
