#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j]) cout << " Q ";
            else cout << " . ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) if (board[i][col]) return false;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) if (board[i][j]) return false;
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) if (board[i][j]) return false;
    return true;
}

bool solveNQUtil(vector<vector<int>>& board, int row, int n) {
    if (row >= n) return true; // All queens placed

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            // STATE TREE GROWTH
            board[row][col] = 1;
            cout << string(row * 2, ' ') << "-> Branching: Placing Queen at (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(100));

            if (solveNQUtil(board, row + 1, n)) return true;

            // BACKTRACKING
            board[row][col] = 0; 
            cout << string(row * 2, ' ') << "<- Backtracking: Removing Queen from (" << row << "," << col << ")\n";
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    return false;
}

void runNQueens() {
    int n = 4; // Using 4x4 so the state tree animation doesn't take hours
    vector<vector<int>> board(n, vector<int>(n, 0));

    cout << "\nSolving " << n << "-Queens Problem...\n";
    if (solveNQUtil(board, 0, n)) {
        cout << "\n=== SOLUTION FOUND ===\n";
        printBoard(board, n);
    } else {
        cout << "Solution does not exist.\n";
    }
}