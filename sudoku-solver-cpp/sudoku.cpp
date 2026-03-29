#include <bits/stdc++.h>
using namespace std;

// Global variables
array<array<int, 9>, 9> sudoku;
array<array<int, 9>, 9> temp;
bool solved = false;
int depth = 0;

// Tree visualization
void printTree(string msg)
{
    for (int i = 0; i < depth; i++)
        cout << "   ";
    cout << msg << endl;
}

// Check row
bool checkrow(int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (sudoku[row][col] == num)
            return false;
    return true;
}

// Check column
bool checkcolumn(int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (sudoku[row][col] == num)
            return false;
    return true;
}

//  Check 3x3 grid
bool checkgrid(int row, int col, int num)
{
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (sudoku[i][j] == num)
                return false;
    return true;
}

//  Print Sudoku
void draw()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << sudoku[i][j] << " ";
            if (j == 2 || j == 5)
                cout << "| ";
        }
        cout << endl;
        if (i == 2 || i == 5)
            cout << "---------------------\n";
    }
}

// Find next empty cell
bool findEmpty(int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (sudoku[row][col] == 0)
                return true;
    return false;
}

// Main function
void solveSudoku()
{
    cout << "Enter Sudoku (9x9), use 0 for empty:\n";

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            cin >> sudoku[i][j];

    cout << "\nInitial Sudoku:\n";
    draw();

    cout << "\nSolving...\n";

    if (solveSudokuRec())
    {
        cout << "\nFinal Solution:\n";
        draw();
    }
    else
    {
        cout << "No solution exists.\n";
    }
}