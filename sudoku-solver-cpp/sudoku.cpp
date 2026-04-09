#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

#define UNASSIGNED 0
#define N 5

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Subgrid checks are removed because a 5x5 grid cannot be divided into uniform square subgrids.
bool isSafe(int grid[N][N], int row, int col, int num)
{
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    return true;
}

// HEURISTIC: Minimum Remaining Values (MRV)
bool findEmptyMRV(int grid[N][N], int &row, int &col)
{
    int minOptions = N + 1; // Max options is 5, so start with 6
    bool found = false;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (grid[r][c] == UNASSIGNED)
            {
                int options = 0;
                for (int num = 1; num <= N; num++)
                {
                    if (isSafe(grid, r, c, num))
                        options++;
                }
                if (options < minOptions)
                {
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

bool solveSudoku(int grid[N][N], int depth = 0)
{
    int row, col;

    // If no empty cell, we are done
    if (!findEmptyMRV(grid, row, col))
    {
        return true;
    }

    // Try numbers 1 to 5
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            // STATE TREE GROWTH: Try placing a number
            grid[row][col] = num;
            cout << string(depth * 2, ' ') << "-> Depth " << depth << ": Trying " << num << " at (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(20)); // Animation pause

            if (solveSudoku(grid, depth + 1))
                return true;

            // BACKTRACKING: Undo the choice
            grid[row][col] = UNASSIGNED;
            cout << string(depth * 2, ' ') << "<- Depth " << depth << ": Backtracking from (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(20)); // Animation pause
        }
    }
    return false; // Trigger backtrack
}

void runSudoku()
{
    // A solvable 5x5 grid puzzle
    int grid[N][N] = {{1, 0, 3, 0, 5},
                      {0, 3, 0, 5, 0},
                      {3, 0, 5, 0, 2},
                      {0, 5, 0, 2, 0},
                      {5, 0, 2, 0, 4}};

    cout << "\nSolving 5x5 Sudoku using MRV Heuristic...\n";
    if (solveSudoku(grid))
    {
        cout << "\n=== SOLUTION FOUND ===\n";
        printGrid(grid);
    }
    else
    {
        cout << "No solution exists.\n";
    }
}

int main()
{
    runSudoku();
    return 0;
}