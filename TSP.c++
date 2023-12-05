#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = INT_MAX;

// Function to solve TSP using dynamic programming
int tsp(int mask, int pos, vector<vector<int>> &graph, vector<vector<int>> &dp) {
    int n = graph.size();

    // If all cities have been visited, return the cost to return to the starting city
    if (mask == (1 << n) - 1) {
        return graph[pos][0];
    }

    // If the result is already computed, return it
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    // Try visiting each unvisited city and choose the minimum cost
    int minCost = INF;
    for (int i = 0; i < n; ++i) {
        if ((mask & (1 << i)) == 0) { // If the i-th city is not visited
            int newMask = mask | (1 << i);
            int cost = graph[pos][i] + tsp(newMask, i, graph, dp);
            minCost = min(minCost, cost);
        }
    }

    // Memoize the result
    return dp[mask][pos] = minCost;
}

// Function to solve TSP using dynamic programming
int solveTSP(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    // Start the TSP from the first city (0)
    return tsp(1, 0, graph, dp);
}

int main() {
    // Example graph representing the distances between cities
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int minCost = solveTSP(graph);

    cout << "Minimum cost of TSP: " << minCost << endl;

    return 0;
}
