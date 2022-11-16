#include "SudokuGame.h"
#include <iostream>
using namespace std;

int main() {

	SudokuGame game = SudokuGame(1);

	while (game.gameRunning) {
		game.Show();
		game.RecieveInput();
	}
	cout << "You won!";
}