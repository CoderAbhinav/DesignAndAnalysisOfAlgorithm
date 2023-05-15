#include <iostream>
#include <vector>
using namespace std;

class TSP {
  #define Graph vector<vector<int>>
private:
  Graph graph;
  int final_res;
  vector<int> final_path;
  vector<bool> visited;

  int firstMin(int node) {
    int res = INT_MAX;
    for (int i = 0; i < graph[node].size(); i++) {
      res = min(res, graph[node][i]);
    }
    return res;
  }

  int secondMin(int node) {
    int first_min = INT_MAX, second_min = INT_MAX;

    for (int i = 0; i < graph[node].size(); i++) {
      if (i == node) continue;

      if (graph[node][i] <= first_min) {
        second_min = first_min;
        first_min = graph[node][i];
      } else if (graph[node][i] <= second_min && graph[node][i] != first_min) {
        second_min = graph[node][i];
      }
    }

    return second_min;
  }

  void TSPRec(vector<int> current_path, int level, int current_bound, int current_weight) {
    if (level == graph.size()) {
      // There exists a path from first to last
      if (graph[current_path[level - 1]][current_path[0]] != 0) {
        int current_res = current_weight + graph[current_path[level - 1]][current_path[0]];

        if (current_res < final_res) {
          final_path = vector<int>(current_path);
          final_res = current_res;
        }
      }
      return;
    }

    for (int i = 0; i < graph.size(); i++) {
      if (graph[current_path[level - 1]][i] != 0 && visited[i] == false) {
        int temp = current_bound;
        current_weight = graph[current_path[level - 1]][i];

        if (current_path.size() == 1) {
          current_bound -= firstMin(current_path[level - 1]) + firstMin(i) / 2;
        } else {
          current_bound -= secondMin(current_path[level - 1]) + firstMin(i) / 2;
        }

        if (current_bound + current_weight < final_res) {
          current_path[level] = i;
          visited[i] = true;

          TSPRec(current_path, level + 1, current_bound, current_weight);

        }

        current_weight -= graph[current_path[current_path.size() - 1]][i];
        current_bound = temp;

        visited = vector<bool>(graph.size(), false);
        for (int j = 0; j <= level - 1; j++) {
          visited[current_path[j]] = true;
        }
      }
    }
  }

public:
  TSP(Graph graph) {
    this->graph = graph;

    visited = vector<bool>(graph.size(), false);
    visited[0] = true;

    vector<int> current_path(graph.size(), 0);

    int curr_bound = 0;

    for (int i = 0; i < graph.size(); i++) {
      curr_bound += (firstMin(i) + secondMin(i));
    }

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    TSPRec(current_path, 1, curr_bound, 0);
  }

  int getPathCost() {
    return this->final_res;
  }

  vector<int> getPath() {
    return this->final_path;
  }
};

int main(int argc, char const *argv[])
{
  Graph g = { {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP t(g);

    cout << t.getPathCost() << "\n";

    vector<int> path = t.getPath();
    for (int i = 0; i < path.size(); i++) {
      cout << path[i] << "\t";
    }
  return 0;
}
