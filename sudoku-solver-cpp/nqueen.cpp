#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<int>& board, int row, int col) {
    for(int i = 0; i < row; i++) {
        if(board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void solve(int n, int row, vector<int>& board) {
    if(row == n) {
        cout << "Solution:\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cout << (board[i] == j ? "Q " : ". ");
            cout << endl;
        }
        cout << endl;
        return;
    }

    for(int col = 0; col < n; col++) {
        cout << "Trying (" << row << "," << col << ")\n";
        if(isSafe(board, row, col)) {
            board[row] = col;
            solve(n, row + 1, board);
        }
    }
}

void solveNQueens() {
    int n;
    cout << "Enter N: ";
    cin >> n;

    vector<int> board(n, -1);
    solve(n, 0, board);
}