#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
//#include<bits/stdc++.h>
using namespace std;

#define UNASSIGNED 0
#define N 9

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    return true;
}

// HEURISTIC: Minimum Remaining Values (MRV)
// Finds the empty cell with the fewest valid options left to reduce the tree size.
bool findEmptyMRV(int grid[N][N], int &row, int &col) {
    int minOptions = 10;
    bool found = false;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == UNASSIGNED) {
                int options = 0;
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, r, c, num)) options++;
                }
                if (options < minOptions) {
                    minOptions = options;
                    row = r;
                    col = c;
                    found = true;
                }
            }
        }
    }
    return found;
}

bool solveSudoku(int grid[N][N], int depth = 0) {
    int row, col;
    
    // If no empty cell, we are done
    if (!findEmptyMRV(grid, row, col)) {
        return true; 
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // STATE TREE GROWTH: Try placing a number
            grid[row][col] = num;
            cout << string(depth, ' ') << "-> Depth " << depth << ": Trying " << num << " at (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(20)); // Animation pause

            if (solveSudoku(grid, depth + 1)) return true;

            // BACKTRACKING: Undo the choice
            grid[row][col] = UNASSIGNED;
            cout << string(depth, ' ') << "<- Depth " << depth << ": Backtracking from (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(20)); // Animation pause
        }
    }
    return false; // Trigger backtrack
}

void runSudoku() {
    int grid[N][N] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
                       {5, 2, 0, 0, 0, 0, 0, 0, 0},
                       {0, 8, 7, 0, 0, 0, 0, 3, 1},
                       {0, 0, 3, 0, 1, 0, 0, 8, 0},
                       {9, 0, 0, 8, 6, 3, 0, 0, 5},
                       {0, 5, 0, 0, 9, 0, 6, 0, 0},
                       {1, 3, 0, 0, 0, 0, 2, 5, 0},
                       {0, 0, 0, 0, 0, 0, 0, 7, 4},
                       {0, 0, 5, 2, 0, 6, 3, 0, 0} };

    cout << "\nSolving Sudoku using MRV Heuristic...\n";
    if (solveSudoku(grid)) {
        cout << "\n=== SOLUTION FOUND ===\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.\n";
    }
}