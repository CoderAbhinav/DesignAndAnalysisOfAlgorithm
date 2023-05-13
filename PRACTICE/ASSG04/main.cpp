#include <iostream>
#include <vector>
#define Graph vector<vector<int>>

using namespace std;

int lower_bound_calculator(Graph graph, int node)
{
    int lower_bound = 0;
    for (int i = 0; i < graph[node].size(); i++)
    {
        if (graph[node][i] != INT_MAX)
        {
            lower_bound += graph[node][i];
        }
    }
    return lower_bound / 2;
}

int branch_and_bound(Graph graph, int prev = -1, int node = 0, int cost = 0, int visited = 0)
{
    if (visited == (1 << graph.size()) - 1)
        return cost;

    int lower_bound = lower_bound_calculator(graph, node) + cost / 2;

    if (cost > lower_bound)
    {
        return INT_MAX;
    }

    int min_cost = INT_MAX, min_cost_vertex = node;

    for (int i = 0; i < graph[node].size(); i++)
    {
        if ((visited & (1 << i)) == 0 && graph[node][i] != INT_MAX && i != prev && i != node)
        {
            int res = branch_and_bound(graph, node, i, cost + graph[node][i], (visited | (1 << i)));
            if (res < min_cost)
            {
                min_cost = res;
                min_cost_vertex = i;
            }
        }
    }

    return min_cost;
}

int main(int argc, char const *argv[])
{
    Graph g = {
        {0, 93, 41, 82, 69}, 
        {93, 0, 64, 36, 36}, 
        {41, 64, 0, 71, 57}, 
        {82, 36, 71, 0, 14}, 
        {69, 36, 57, 14, 0}};

    cout << branch_and_bound(g) << "\t";

    return 0;
}
