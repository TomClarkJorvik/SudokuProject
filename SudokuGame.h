#pragma once
#include "SudokuBoard.h"
#define N 9

class SudokuGame
{
public:
	
	SudokuBoard* board;
	bool gameRunning;

	SudokuGame(int difficulty);

	void Show();
	void ShowHiddenBoard();
	void RecieveInput();
	bool TakeAction(int row, int col, int number);
};

