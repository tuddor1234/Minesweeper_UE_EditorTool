#pragma once
#include "Widgets/Layout/SScaleBox.h"

DECLARE_DELEGATE_ThreeParams(TileClickedDelaegate, int32, int32, int32);
class STile: public SScaleBox
{
	SLATE_DECLARE_WIDGET(STile, SScaleBox)
public:
	SLATE_BEGIN_ARGS(STile){}
		SLATE_ARGUMENT(int32 , NumAdjBombs)
		SLATE_ARGUMENT(int32 , Row)
		SLATE_ARGUMENT(int32 , Col)
		SLATE_EVENT(TileClickedDelaegate, OnTileClicked)
	SLATE_END_ARGS();

	void Construct(const FArguments& Args);

	int GetRow() const {return m_Row;}
	int GetCol() const {return m_Col;}
	bool IsBomb() const { return NumBombs == -1;}
	bool IsRevealed() const {return m_bRevealed;}
	
	void SetNumAdjBombs(int Bombs) {NumBombs = Bombs;}
	void SetGameState(bool GameOver) { m_bGameOver = GameOver; }
	void Reveal()
	{
		m_bRevealed = true;
		OnTileClicked.ExecuteIfBound(NumBombs, m_Row, m_Col);
	}
private:
	const FSlateBrush* GetBrushByNumBombs() const;
private:
	bool m_bRevealed = false, m_bGameOver = false;
	int NumBombs = 0, m_Row, m_Col;

	TileClickedDelaegate OnTileClicked;
};
