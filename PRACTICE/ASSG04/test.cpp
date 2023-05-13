#include <iostream>
#include <vector>

using namespace std;

// This function calculates the lower bound of the cost of the TSP tour starting at the given node.
int lower_bound_calc(const vector<vector<int>>& distances, int node) {
  int lower_bound = 0;
  for (int i = 0; i < distances[node].size(); i++) {
    if (distances[node][i] != INT_MAX) {
      lower_bound += distances[node][i];
    }
  }
  return lower_bound / 2;
}

// This function recursively searches for the TSP tour with the minimum cost.
int branch_and_bound(const vector<vector<int>>& distances, int node, int visited, int cost) {
  // If the node has been visited, return INT_MAX.
  if (visited == (1 << distances.size()) - 1) {
    return INT_MAX;
  }

  // Calculate the lower bound of the cost of the TSP tour starting at the given node.
  int lower_bound = lower_bound_calc(distances, node);

  // If the cost of the current tour is greater than the lower bound, there is no need to explore it further.
  if (cost > lower_bound) {
    return INT_MAX;
  }

  // Otherwise, explore all possible next nodes and return the minimum cost of the TSP tour found.
  int min_cost = INT_MAX;
  for (int i = 0; i < distances[node].size(); i++) {
    if ((visited & (1 << i)) == 0 && distances[node][i] != INT_MAX) {
      min_cost = min(min_cost, branch_and_bound(distances, i, visited | (1 << i), cost + distances[node][i]));
    }
  }

  return min_cost;
}

// This function solves the Traveling Salesman Problem using Branch and Bound.
int solve_tsp(const vector<vector<int>>& distances) {
  // Initialize the visited set to empty.
  int visited = 0;

  // Return the cost of the TSP tour with the minimum cost.
  return branch_and_bound(distances, 0, visited, 0);
}

int main() {
  // Create a vector of distances between cities.
  vector<vector<int>> distances = {{0, 10, 20, 30},
                                    {10, 0, 40, 50},
                                    {20, 40, 0, 60},
                                    {30, 50, 60, 0}};

  // Print the cost of the TSP tour with the minimum cost.
  cout << solve_tsp(distances) << endl;

  return 0;
}