#include "STile.h"

#include "GeoTechMinesweeperStyle.h"

SLATE_IMPLEMENT_WIDGET(STile)
void STile::PrivateRegisterAttributes(FSlateAttributeInitializer& AttributeInitializer) {}

void STile::Construct(const FArguments& Args)
{
	OnTileClicked = Args._OnTileClicked;
	NumBombs = Args._NumAdjBombs;
	m_Row = Args._Row;
	m_Col = Args._Col;

	SetStretch(EStretch::Type::ScaleToFit);
	
	ChildSlot
	[
		SNew(SImage)
		.Image_Raw(this, &STile::GetBrushByNumBombs)
		.OnMouseButtonDown_Lambda([this](const FGeometry&, const FPointerEvent&) -> FReply
		{
			if (m_bGameOver)
				return FReply::Unhandled();
			
			Reveal();
			return FReply::Handled();
		})
	];
}

const FSlateBrush* STile::GetBrushByNumBombs() const
{
	auto GetBrushByName = [this](const FString& Name)
	{
		return FGeoTechMinesweeperStyle::Get().GetBrush(FName(Name));
	};
	
	if (!m_bRevealed)
		return GetBrushByName("GTM.Default");

	// If it's -1 it's a bomb
	if (NumBombs < 0)
		return GetBrushByName("GTM.Mine");

	return GetBrushByName("GTM." + FString::FromInt(NumBombs));
}
