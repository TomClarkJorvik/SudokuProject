#include "SudokuGame.h"
#include <iostream>
using namespace std;

SudokuGame::SudokuGame(int difficulty)
{
	gameRunning = true;
	cout << "When asked for row input, type r to reset the board to only known numbers, type c to check which numbers are correct,\ntype k to show known numbers, or type a number to proceed to take an action.\n\n";
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
	string firstInput;
	char* endptr = nullptr;
	const char* input_ptr;
	int value; 
	bool firstInputIsNumber;

	int row = 0;
	int col = 0;
	int number = 0;
	bool legalInput = false;
	while (!legalInput) {
		firstInputIsNumber = false;
		// handles whether the first input is a character or an integer.
		while (!firstInputIsNumber) {
			cout << endl << "Row: ";
			cin >> firstInput;
			input_ptr = firstInput.c_str();
			if (firstInput.size() == 1) {
				if (firstInput[0] == 'r' || firstInput[0] == 'R') {
					std::cout << "Resetting board to only known numbers." << std::endl;
					board->ResetBoardToKnown();
					board->Show();
				}
				else if (firstInput[0] == 'c' || firstInput[0] == 'C') {
					std::cout << "Checking board for known numbers.\nShowing known numbers." << std::endl;
					board->CheckForKnownNumbers();
					board->ShowKnownBoard();
				}
				else if (firstInput[0] == 'k' || firstInput[0] == 'K') {
					std::cout << "Outputting only known numbers." << std::endl;
					board->ShowKnownBoard();
				}
				else {
					row = std::strtol(input_ptr, &endptr, 10);
					firstInputIsNumber = true;
				}
			}
			else {
				row = std::strtol(input_ptr, &endptr, 10);
				firstInputIsNumber = true;
			}
		}
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
