#pragma once
#include <vector>

class TravellingSalesmansProblem
{

    #define Graph std::vector<std::vector<int>>
    #define Path std::vector<int>
private:
    Graph graph;
    Path bestPath;
    int minCost;

    void reduceMatrix(Graph&);
    int calculatePathCost(Path& path);

    void branchAndBound(Path&, int, int);
public:
    TravellingSalesmansProblem(Graph &);
    ~TravellingSalesmansProblem();

    int getPathCost();
    Path getPath();
};

TravellingSalesmansProblem::TravellingSalesmansProblem(Graph &graph)
{
    int n = graph.size();
    this->minCost = INT_MAX;
    this->graph = graph;
    Path path(n); path[0] = 0;

    reduceMatrix(graph);
    branchAndBound(path, 0, 0);
}

TravellingSalesmansProblem::~TravellingSalesmansProblem()
{
}

void TravellingSalesmansProblem::reduceMatrix(Graph &matrix)
{
    int n = matrix.size();
    // Reduce each row
    for (int i = 0; i < n; ++i)
    {
        int minVal = INT_MAX;
        /// Find the minimum value in current row
        for (int j = 0; j < n; ++j)
        {
            if (matrix[i][j] < minVal)
            {
                minVal = matrix[i][j];
            }
        }

        /// Reduce each row
        for (int j = 0; j < n; ++j)
        {
            matrix[i][j] -= minVal;
        }
    }

    // Reduce each column
    for (int i = 0; i < n; ++i)
    {
        int minVal = INT_MAX;
        /// Find the minimum value in current column
        for (int j = 0; j < n; ++j)
        {
            if (matrix[j][i] < minVal)
            {
                minVal = matrix[j][i];
            }
        }
        /// Reduce each column
        for (int j = 0; j < n; ++j)
        {
            matrix[j][i] -= minVal;
        }
    }
}


int TravellingSalesmansProblem::calculatePathCost(Path& path) {
    int cost = 0, n = graph.size();
    for (int i = 0; i < n - 1; i++) {
        cost += graph[path[i]][path[i + 1]];
    }

    cost += graph[path[n - 1]][path[0]];

    return cost;
}

void TravellingSalesmansProblem::branchAndBound(Path& path, int level, int visited ) {
    int n = path.size();
    
    // if (cost > minCost) return;

    /// If all the nodes are visited    
    if (level == n - 1) {
        /// Check if current cost is minimum
        int cost = calculatePathCost(path);
        if (cost < minCost) {
            minCost = cost;
            bestPath = path;
        }
        return;
    }



    for (int i = 0; i < n; i++) {

        if ((visited & (1 << i)) == false) {
            path[level + 1] = i;
            Graph newMatrix;
            reduceMatrix(newMatrix);
            branchAndBound(path, level + 1, (visited | (1 << i)));
        }
    }
}

int TravellingSalesmansProblem::getPathCost() {
    return minCost;
}


Path TravellingSalesmansProblem::getPath() {
    return bestPath;
}