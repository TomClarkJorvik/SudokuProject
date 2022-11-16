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

	bool CheckColumn(int col, int number, int** inputBoard);
	bool CheckRow(int row, int number, int** inputBoard);
	bool CheckBlock(int boxInitialRow, int boxInitialCol, int number, int** inputBoard);

	int TakeAction(int row, int col, int number);
	void Show();
	void ShowKnownBoard();
	void ShowHiddenBoard();
	void ShowSolvedBoard();

	bool CheckIfWon();
	void CheckForKnownNumbers();
	void ResetBoardToKnown();

	bool SudokuSolver(int** inputBoard); 
private:
	void CreateHiddenFullBoard();
	bool SudokuSolverRecursion();
	bool FindEmptyLocation(int arr[2]);

	int basicBoard[9][9] = { {1, 2, 3, 4, 5, 6, 7, 8, 9},
							{4, 5, 6, 7, 8, 9, 1, 2, 3},
							{7, 8, 9, 1, 2, 3, 4, 5, 6},
							{2, 3, 1, 5, 6, 4, 8, 9, 7},
							{5, 6, 4, 8, 9, 7, 2, 3, 1},
							{8, 9, 7, 2, 3, 1, 5, 6, 4},
							{3, 1, 2, 6, 4, 5, 9, 7, 8},
							{6, 4, 5, 9, 7, 8, 3, 1, 2},
							{9, 7, 8, 3, 1, 2, 6, 4, 5} };

	int** sudokuSolverBoard;
};