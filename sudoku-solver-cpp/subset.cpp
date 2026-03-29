#include <bits/stdc++.h>
using namespace std;

void subset(vector<int>& arr, int i, int sum, int target, vector<int>& path) {
    if(sum == target) {
        cout << "Subset: ";
        for(int x : path) cout << x << " ";
        cout << endl;
        return;
    }

    if(i == arr.size() || sum > target) return;

    // Include
    path.push_back(arr[i]);
    subset(arr, i+1, sum + arr[i], target, path);

    // Backtrack
    path.pop_back();
    subset(arr, i+1, sum, target, path);
}

void solveSubset() {
    int n, target;
    cout << "Enter size: ";
    cin >> n;

    vector<int> arr(n);
    for(int i=0;i<n;i++) cin >> arr[i];

    cout << "Target sum: ";
    cin >> target;

    vector<int> path;
    subset(arr, 0, 0, target, path);
}
