#include "SudokuGame.h"
#include <iostream>
using namespace std;

int main() {

	SudokuGame game = SudokuGame(1);
	game.Show();
	cout << game.board->SudokuSolver(game.board->board)<<endl;
	game.board->ShowSolvedBoard();
	//while (game.gameRunning) {
	//	game.Show();
	//	game.RecieveInput();
	//}
	//cout << "You won!";
}