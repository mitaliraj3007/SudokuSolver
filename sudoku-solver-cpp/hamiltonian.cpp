#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

#define V 5

bool isSafe(int v, bool graph[V][V], vector<int>& path, int pos) {
    if (!graph[path[pos - 1]][v]) return false; // Must be connected to previous
    for (int i = 0; i < pos; i++) {
        if (path[i] == v) return false; // Must not be visited already
    }
    return true;
}

bool hamCycleUtil(bool graph[V][V], vector<int>& path, int pos) {
    if (pos == V) {
       
        if (graph[path[pos - 1]][path[0]]) return true;
        else return false;
    }

    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            // STATE TREE GROWTH
            path[pos] = v;
            cout << string(pos * 2, ' ') << "-> Trying Vertex " << v << " at position " << pos << "\n";
            this_thread::sleep_for(chrono::milliseconds(250));

            if (hamCycleUtil(graph, path, pos + 1)) return true;

            // BACKTRACKING
            path[pos] = -1;
            cout << string(pos * 2, ' ') << "<- Backtracking: Removing Vertex " << v << " from position " << pos << "\n";
            this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    return false;
}

void runHamiltonianCycle() {
    // Adjacency Matrix for the graph
    bool graph[V][V] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0}
    };

    vector<int> path(V, -1);
    path[0] = 0; // Start at vertex 0

    cout << "\nSolving Hamiltonian Cycle...\n";
    if (hamCycleUtil(graph, path, 1)) {
        cout << "\n=== SOLUTION FOUND ===\nPath: ";
        for (int i = 0; i < V; i++) cout << path[i] << " -> ";
        cout << path[0] << "\n"; // Print return to start
    } else {
        cout << "No Hamiltonian Cycle exists.\n";
    }
}