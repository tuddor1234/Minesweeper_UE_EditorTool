#include "MinesweeperGame.h"
#include "SMinesweeperSetting.h"
#include "STile.h"

FReply MinesweeperGame::OnNewGamePressed()
{
	ResetUI();
	FillBombs();
	return FReply::Handled();
}

TSharedRef<SWidget> MinesweeperGame::GetGUI()
{
	return SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5)
		[
			GetSettingsArea()
		]
		+SVerticalBox::Slot()
		.VAlign(VAlign_Center)
		.AutoHeight()
		.Padding(5)
		[
			SNew(SButton)
			.Text(FText::FromString("New Game"))
			.OnClicked_Raw(this, &MinesweeperGame::OnNewGamePressed)
		]
		+SVerticalBox::Slot()
		.FillHeight(1).Padding(5)
		[
			GetGameArea()
		];
}

TSharedRef<SWidget> MinesweeperGame::GetSettingsArea()
{
	return SNew(SVerticalBox)
	+SVerticalBox::Slot()
	[
		SNew(SMinesweeperSetting)
		.LabelText("Width")
		.InitialValue(m_Width)
		.OnValueChanged_Lambda([this](int32 NewWidth){m_Width = NewWidth;})
	]
	+SVerticalBox::Slot()
	[
		SNew(SMinesweeperSetting)
		.LabelText("Height")
		.InitialValue(m_Height)
		.OnValueChanged_Lambda([this](int32 NewHeight) {m_Height = NewHeight;})
	]
	+SVerticalBox::Slot()
	[
		SNew(SMinesweeperSetting)
		.LabelText("Num Bombs")
		.InitialValue(m_NumBombs)
		.OnValueChanged_Lambda([this](int32 NewNumBombs){m_NumBombs = NewNumBombs;})
	];
}

TSharedRef<SWidget> MinesweeperGame::GetGameArea()
{
	
	return SNew(SOverlay)
		+SOverlay::Slot()
		[
			SAssignNew(m_GridPanel, SGridPanel)
		]
		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(SBorder)
			.Visibility_Lambda([this](){return m_bGameOver ? EVisibility::Visible : EVisibility::Hidden; })
			.BorderBackgroundColor(FLinearColor::Red)
			[
				SNew(STextBlock)
				.Text(FText::FromString("GAME OVER"))
				.ColorAndOpacity(FLinearColor::Red)
			]
		];
}

void MinesweeperGame::GamePause(bool bGameRunning)
{
	m_bGameOver = bGameRunning;
	for (int i = 0; i < m_Height; ++i)
	{
		for (int j = 0; j < m_Width; ++j)
		{
			m_Grid[i][j]->SetGameState(bGameRunning);
		}
	}
}

void MinesweeperGame::OnTileClicked(int bombCount, int row, int col)
{
	// It's bomb, Game Over
	if (bombCount == -1)
	{
		GamePause(true);
	}

	// If it's empty space, Reveal Recursively
	if (bombCount == 0)
	{
		// UP
		if (row > 0 && !m_Grid[row-1][col]->IsRevealed())
			m_Grid[row-1][col]->Reveal();

		// DOWN
		if (row < m_Height - 1 && !m_Grid[row+1][col]->IsRevealed())
			m_Grid[row+1][col]->Reveal();

		// LEFT
		if (col > 0 && !m_Grid[row][col-1]->IsRevealed())
			m_Grid[row][col-1]->Reveal();

		// RIGHT
		if (col < m_Width - 1 && !m_Grid[row][col+1]->IsRevealed())
			m_Grid[row][col+1]->Reveal();
		
	}

	// Don't do anything if it's a number
}

void MinesweeperGame::ResetUI()
{
	m_bGameOver = false;
	m_GridPanel->ClearChildren();
	m_GridPanel->ClearFill();
	
	m_Grid.SetNum(m_Height);
	for (int32 i = 0; i < m_Height; ++i)
	{
		m_GridPanel->SetRowFill(i, 1);
		m_Grid[i].SetNum(m_Width);
		
		for (int32 j = 0; j < m_Width; ++j)
		{
			auto slot = m_GridPanel->AddSlot(j,i);
			slot.AttachWidget(
				SAssignNew(m_Grid[i][j],STile)
				.OnTileClicked_Raw(this, &MinesweeperGame::OnTileClicked)
				.Row(i).Col(j)
			);
			slot.Padding(5);
		}
	}

	for (int32 j = 0; j < m_Width; ++j)
		m_GridPanel->SetColumnFill(j, 1);

	GamePause(false);
}

int MinesweeperGame::GetBombCount(int32 row, int col)
{
	int bombCount = 0;

	// Up
	if (row > 0)
		bombCount += m_Grid[row-1][col]->IsBomb();
	
	// UpRight
	if (row > 0 && col < m_Width-1)
		bombCount += m_Grid[row-1][col+1]->IsBomb();

	// Right
	if (col < m_Width-1)
		bombCount += m_Grid[row][col+1]->IsBomb();

	// DownRight
	if (row < m_Height-1 && col < m_Width-1)
		bombCount += m_Grid[row+1][col+1]->IsBomb();

	// Down
	if (row < m_Height-1)
		bombCount += m_Grid[row+1][col]->IsBomb();

	// DownLeft
	if (row < m_Height-1 && col > 0)
		bombCount += m_Grid[row+1][col-1]->IsBomb();

	// Left	
	if (col > 0)
		bombCount += m_Grid[row][col-1]->IsBomb();

	// UpLeft
	if (row > 0 && col > 0)
		bombCount += m_Grid[row-1][col-1]->IsBomb();
	
	return bombCount;
}

void MinesweeperGame::FillBombs()
{
	// Choose Randomly the positions of the bombs
	for (int index = 0;  index < m_NumBombs; ++index)
	{
		int i = FMath::RandRange(0, m_Height-1);
		int j = FMath::RandRange(0, m_Width-1);

		m_Grid[i][j]->SetNumAdjBombs(-1);
	}

	// FIll the rest of the grid
	for (int i = 0 ; i < m_Height; ++i)
	{
		for (int j = 0 ; j < m_Width; ++j)
		{
			if (m_Grid[i][j]->IsBomb())
				continue;

			m_Grid[i][j]->SetNumAdjBombs(GetBombCount(i,j));
		}
	}
}

