#include "SudokuBoard.h"
#include <iostream>
using namespace std;

SudokuBoard::SudokuBoard(int difficulty)
{
    if (difficulty > 4) {
        difficulty = 4;
    }
    CreateHiddenFullBoard();
    CreateBoard(difficulty);
}

void SudokuBoard::CreateBoard(int difficulty) {
    board = new int* [N];
    knownBoard = new int* [N];
    for (int i = 0; i < N; i++)
    {
        board[i] = new int[N];
        knownBoard[i] = new int[N];

        for (int j = 0; j < N; j++)
        {
            /* generate secret number between 1 and 5: */
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(1, 5);
            int randomNumber = distr(gen);

            if (randomNumber <= difficulty+1) {
                board[i][j] = 0;
                knownBoard[i][j] = 0;
            }

            else {
                board[i][j] = hiddenFullBoard[i][j];
                knownBoard[i][j] = hiddenFullBoard[i][j];
            }
        }
    }
}


void SudokuBoard::CreateHiddenFullBoard()
{

    hiddenFullBoard = new int* [N];
    for (int i = 0; i < N; i++)
    {
        hiddenFullBoard[i] = new int[N];

        for (int j = 0; j < N; j++)
        {
            hiddenFullBoard[i][j] = basicBoard[i][j];
        }
    }

    // shuffle
    // while numberOfSolutions > 1
    //       shuffle again
 
    int numberOfSolutions = SudokuSolver(hiddenFullBoard);

}

bool SudokuBoard::CheckColumn(int col, int number, int** inputBoard)
{
    for (int i = 0; i < N; i++) {
        if (inputBoard[i][col] == number) {
            return true;
        }
    }
    return false;
}

bool SudokuBoard::CheckRow(int row, int number, int** inputBoard)
{
    for (int j = 0; j < N; j++) {
        if (inputBoard[row][j] == number) {
            return true;
        }
    }
    return false;
}

bool SudokuBoard::CheckBlock(int boxInitialRow, int boxInitialCol, int number, int** inputBoard)
{
    for (int i = boxInitialRow; i < boxInitialRow + 3; i++)
    {
        for (int j = boxInitialCol; j < boxInitialCol + 3; j++) {
            if (inputBoard[i][j] == number) {
                return true;
            }
        }

    }

    return false;
}


bool SudokuBoard::CheckColumn(int col, int number)
{
    for (int i = 0; i < N; i++) {
        if (board[i][col] == number) {
            return true;
        }
    }
    return false;
}

bool SudokuBoard::CheckRow(int row, int number)
{
    for (int j = 0; j < N; j++) {
        if (board[row][j] == number) {
            return true;
        }
    }
    return false;
}

bool SudokuBoard::CheckBlock(int boxInitialRow, int boxInitialCol, int number)
{
    for (int i = boxInitialRow; i < boxInitialRow + 3; i++)
    {
        for (int j = boxInitialCol; j < boxInitialCol + 3; j++) {
            if (board[i][j] == number) {
                return true;
            }
        }

    }

    return false;

}

void SudokuBoard::Show()
  {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        if (i % 3 == 2 && i != N - 1) {
            cout << endl;
            for (int z = 0; z < N; z++) {

                if (z % 3 == 0 && z != 0) {
                    cout << "| ";
                }

                cout << "- ";

            }
        }
        cout << endl;
    }
}

void SudokuBoard::ShowKnownBoard()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << knownBoard[i][j] << " ";
        }
        if (i % 3 == 2 && i != N - 1) {
            cout << endl;
            for (int z = 0; z < N; z++) {

                if (z % 3 == 0 && z != 0) {
                    cout << "| ";
                }

                cout << "- ";

            }
        }
        cout << endl;
    }
}

void SudokuBoard::ShowHiddenBoard()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << hiddenFullBoard[i][j] << " ";
        }
        if (i % 3 == 2 && i != N - 1) {
            cout << endl;
            for (int z = 0; z < N; z++) {

                if (z % 3 == 0 && z != 0) {
                    cout << "| ";
                }

                cout << "- ";

            }
        }
        cout << endl;
    }
}

int SudokuBoard::TakeAction(int row, int col, int number)
{
    if (knownBoard[row][col] == 0) {
        if (!CheckRow(row, number) && !CheckColumn(col, number) && !CheckBlock((row / 3) * 3, (col / 3) * 3,number)) {
            // if the number can fit in that row, column and block, then add it to the board and return 0.
            board[row][col] = number;
            return 0;
        }
        else {
            // if the number is already present in that row, column or block, then return 1.
            return 1;
        }
    }
    else {
        // if attempting to replace a "known" number, return 2.
        return 2;
    }
    
}

bool SudokuBoard::CheckIfWon()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != hiddenFullBoard[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void SudokuBoard::CheckForKnownNumbers()
{
    // if a number is correctly placed, it will add it to the known board.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == hiddenFullBoard[i][j]) {
                knownBoard[i][j] = hiddenFullBoard[i][j];
            }
        }
    }
}

void SudokuBoard::ResetBoardToKnown()
{
    // Resets the board to only have numbers that are known to be correct.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            board[i][j] = knownBoard[i][j];
        }
    }
}

int SudokuBoard::SudokuSolver(int** inputBoard)
{
    sudokuSolverBoard = new int* [N];
    for (int i = 0; i < N; i++)
    {
        sudokuSolverBoard[i] = new int[N];

        for (int j = 0; j < N; j++)
        {
            sudokuSolverBoard[i][j] = inputBoard[i][j];
        }
    }
    return SudokuSolverRecursion();
}

int SudokuBoard::SudokuSolverRecursion()
{
    int arr[2] = { 0,0 };
    // if no empty locations, then it is finished.
    if (!FindEmptyLocation(arr)) {
        return true;
    }

    int numberOfSolutions = 0;
    int returned = 0;
    int row = arr[0];
    int col = arr[1];
    for (int i = 1; i < N + 1; i++) {
        // if the value can be placed
        if (!CheckRow(row, i, sudokuSolverBoard) && !CheckColumn(col, i, sudokuSolverBoard) && !CheckBlock((row / 3) * 3, (col / 3) * 3, i, sudokuSolverBoard)) {
            // test the possible value.
            sudokuSolverBoard[row][col] = i;
            returned = SudokuSolverRecursion();
            numberOfSolutions += returned;
            sudokuSolverBoard[row][col] = 0;

        }
    }
    return numberOfSolutions;


}

bool SudokuBoard::FindEmptyLocation(int arr[2])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            if (sudokuSolverBoard[i][j] == 0) {
                arr[0] = i;
                arr[1] = j;
                return true;
            }
        }
    }
    return false;
}
