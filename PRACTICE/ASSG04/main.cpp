#include <iostream>
#include <vector>
#include "tspbnb.h"


using namespace std;

int main() {
    // Example usage
    Graph g =
        {{0, 10, 15, 20},
         {10, 0, 35, 25},
         {15, 35, 0, 30},
         {20, 25, 30, 0}};

    TravellingSalesmansProblem t(g);
    cout << t.getPathCost() << "\n";

    vector<int> path = t.getPath();

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << "\t";
    }
    return 0;
}
