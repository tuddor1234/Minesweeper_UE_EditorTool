#pragma once
#include "CoreMinimal.h"

class STile;

class MinesweeperGame
{
	
public:
	FReply OnNewGamePressed();
	TSharedRef<SWidget> GetGUI();


private:
	TSharedRef<SWidget> GetSettingsArea();
	TSharedRef<SWidget> GetGameArea();

	void GamePause(bool bGameRunning);
	void OnTileClicked(int bombCount, int tileRow, int tileCol);
	void ResetUI();
	void FillBombs();
	int GetBombCount(int row, int col);
private:

	int m_Width = 10, m_Height = 10, m_NumBombs = 15;

	TArray<TArray<TSharedPtr<STile>>> m_Grid;
	TSharedPtr<SGridPanel> m_GridPanel;
	bool m_bGameOver = false;
};
