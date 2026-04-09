#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

void printSubset(const vector<int> &subset)
{
    cout << "[ ";
    for (int val : subset)
        cout << val << " ";
    cout << "]";
}

void subsetSum(vector<int> &set, vector<int> &subset, int index, int currentSum, int targetSum)
{
    if (currentSum == targetSum)
    {
        cout << "\n>>> VALID SUBSET FOUND: ";
        printSubset(subset);
        cout << " <<<\n\n";
        return; // Find all solutions, so we return instead of exit
    }

    // Pruning rule:
    if (currentSum > targetSum || index >= set.size())
    {
        return;
    }

    // STATE TREE:
    subset.push_back(set[index]);
    cout << string(index * 2, ' ') << "-> Including " << set[index] << " (Sum: " << currentSum + set[index] << ")\n";
    this_thread::sleep_for(chrono::milliseconds(150));

    subsetSum(set, subset, index + 1, currentSum + set[index], targetSum);

    // STATE TREE: Branch 2
    subset.pop_back();
    cout << string(index * 2, ' ') << "<- Backtracking: Excluding " << set[index] << " (Sum reverts to: " << currentSum << ")\n";
    this_thread::sleep_for(chrono::milliseconds(150));

    subsetSum(set, subset, index + 1, currentSum, targetSum);
}

void runSumOfSubsets()
{
    vector<int> set = {10,7,5, 18, 12, 20, 15};
    vector<int> subset;
    int targetSum = 35;

    cout << "\nFinding Subsets that sum to " << targetSum << "...\n";
    subsetSum(set, subset, 0, 0, targetSum);
    cout << "Finished searching tree.\n";
}