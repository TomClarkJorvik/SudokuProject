#pragma once
#include <random>
#define N 9
class SudokuBoard
{
public:
	SudokuBoard(int difficulty);
	void CreateBoard(int difficulty);
	int** board;
	int** hiddenFullBoard;
	int** knownBoard;

	bool CheckColumn(int col, int number);
	bool CheckRow(int row, int number);
	bool CheckBlock(int boxInitialRow, int boxInitialCol, int number);

	int TakeAction(int row, int col, int number);
	void Show();
	void ShowHiddenBoard();

	bool CheckIfWon();
	void CheckForKnownNumbers();
	void ResetBoardToKnown();

private:
	void CreateHiddenFullBoard();

	int basicBoard[9][9] = { {1, 2, 3, 4, 5, 6, 7, 8, 9},
							{4, 5, 6, 7, 8, 9, 1, 2, 3},
							{7, 8, 9, 1, 2, 3, 4, 5, 6},
							{2, 3, 1, 5, 6, 4, 8, 9, 7},
							{5, 6, 4, 8, 9, 7, 2, 3, 1},
							{8, 9, 7, 2, 3, 1, 5, 6, 4},
							{3, 1, 2, 6, 4, 5, 9, 7, 8},
							{6, 4, 5, 9, 7, 8, 3, 1, 2},
							{9, 7, 8, 3, 1, 2, 6, 4, 5} };


};