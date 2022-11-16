#include "SudokuGame.h"
#include <iostream>
using namespace std;

SudokuGame::SudokuGame(int difficulty)
{
	gameRunning = true;
	board = new SudokuBoard(difficulty);
}

void SudokuGame::Show()
{
	board->Show();
}

void SudokuGame::ShowHiddenBoard()
{
	board->ShowHiddenBoard();
}

void SudokuGame::RecieveInput()
{
	int row = 0;
	int col = 0;
	int number = 0;
	bool legalInput = false;
	while (!legalInput) {
		cout << endl << "Row: ";
		cin >> row;
		cout << "Column: ";
		cin >> col;
		cout << "Number: ";
		cin >> number;
		cout << endl;
		legalInput = TakeAction(row-1,col-1,number);
	}

}

// return true if action was legal, false otherwise.
bool SudokuGame::TakeAction(int row, int col, int number)
{
	if (row > 8 || row < 0) {
		cout << "Enter a row between 1 and 9." << endl;
		return false;
	}
	else if (col > 8 || col < 0) {
		cout << "Enter a column between 1 and 9." << endl;
		return false;
	}
	else if (number > 9 || number < 1) {
		cout << "Enter a number between 1 and 9." << endl;
		return false;
	}


	int resultOfAction = board->TakeAction(row, col, number);
	switch (resultOfAction) {
	case 0:
		// if the game is won, set gameRunning to false.
		gameRunning = !(board->CheckIfWon());
		return true;
	case 1:
		cout << "Number already present in row, column or block." << endl;
		return false;
	case 2:
		cout << "That number is already known." << endl;
		return false;
	}

}
