#include <iostream>
using namespace std;

void runNQueens();
void runSumOfSubsets();
void runSudoku();
void runHamiltonianCycle();

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "          PUZZLE SOLVER SUITE            \n";
    cout << "=========================================\n";
    cout << "1. N-Queens (State Tree & Backtracking)\n";
    cout << "2. Sum of Subsets (State Tree)\n";
    cout << "3. Sudoku (MRV Heuristic & Pruning)\n";
    cout << "4. Hamiltonian Cycle\n";
    cout << "5. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice (1-5): ";
}

int main() {
    int choice = 0;
    while (choice != 5) {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1: runNQueens(); break;
            case 2: runSumOfSubsets(); break;
            case 3: runSudoku(); break;
            case 4: runHamiltonianCycle(); break;
            case 5: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    }
    return 0;
}