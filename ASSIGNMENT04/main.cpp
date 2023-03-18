#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;



/**
 * @brief Class Implements easy interface for manipulating graph
 */
class Graph {
    vector<vector<int> > adjacencyMatrix; 
    bool directed;
public:
    /**
     * @brief Construct a new Graph object
     */
    Graph() {}

    /**
     * @brief Construct a new Graph object
     * @param maxVertex the maximum nodes available
     * @param directed directionality of edges
     */
    Graph(int maxVertex, bool directed = false) {
        adjacencyMatrix = vector<vector<int> >(maxVertex, vector<int>(maxVertex, INT_MAX));
        this->directed = directed;
    }

    /**
     * @brief checks if the graph is directed
     * 
     * @return true if directed
     * @return false if undirected
     */
    bool isDirected() {
        return directed;
    }

    /**
     * @brief adds an edge to the graph
     * 
     * @param u the start vertex
     * @param v the end vertex
     * @param weight the weight of edge
     */
    void addEdge(int u, int v,  int weight = 0) {
        adjacencyMatrix[u][v] = weight;
        if (!directed) adjacencyMatrix[v][u] = weight;
    }

    /**
     * @brief check if there is an direct edge between given two nodes
     * @param u the start node
     * @param v the end node
     * @return true 
     * @return false 
     */
    bool existsEdgeBetween(int u, int v) {
        return adjacencyMatrix[u][v] != INT_MAX;
    }

    /**
     * @brief Get the Direct Edge Weight between two vertex
     * @param u the start node
     * @param v the end node
     * @return int 
     */
    int getEdgeWeight(int u, int v) {
        return adjacencyMatrix[u][v];
    }

    /**
     * @brief Get the Adjacency Matix of Graph
     * @return vector<vector<int> >&
     */
    vector<vector<int> >& getAdjacencyMatix() {
        return adjacencyMatrix;
    }

    /**
     * @brief Get the Vertex Count of Graph
     * @return int 
     */
    int getVertexCount() {
        return adjacencyMatrix.size();
    }
};


class TravellingSalesmansProblem {
    Graph graph;
    vector<int> answer;
    int bound;


    void logic(Graph& g, vector<int>& route, int& bound, int current, int cost = 0, int depth = 1) {
        route.push_back(current);

        if (depth == g.getVertexCount()) {
            if (cost < bound) {
                answer.assign(route.begin(), route.end());
                bound = cost;
            }

            route.pop_back();
            return;
        }


        priority_queue<pair<int, int> > nextVertex;
        unordered_set<int> vis(route.begin(), route.end());

        for (int i = 0; i < g.getVertexCount(); i++) {
            if (g.existsEdgeBetween(current, i)) {
                nextVertex.push(make_pair(-1 * (cost + g.getEdgeWeight(current, i)), i));
            }
        }

        while (!nextVertex.empty()) {
            pair<int, int> nextNode = nextVertex.top(); nextVertex.pop();
            if (-1 * nextNode.first < bound && vis.find(nextNode.second) == vis.end()) {
                logic(g, route, bound, nextNode.second, -1 * nextNode.first, depth + 1);
            }
        }

        route.pop_back();
    }

public:
    /**
     * @brief Construct a new Travelling Salesmans Problem object
     * @param graph 
     */
    TravellingSalesmansProblem(Graph& graph, int start = 0) {
        this->graph = graph;
        this->bound = INT_MAX;
        vector<int> temp;
        logic(graph, temp, bound, start);
        bound += graph.getEdgeWeight(answer.back()--, start);
        answer.push_back(start);
    }


    vector<int>& getAnswer() {
        return answer;
    }

    int getCost() {
        return bound;
    }

};



/**
 * @brief this function implements user interaction
 * @param caseNo 
 */
void solve(int caseNo) {
    cout << "\n#TESTCASE: " << caseNo << "\n";
    int vertexCount, edgeCount; cin >> vertexCount >> edgeCount;
    
    Graph g(vertexCount);

    for (int i = 0; i < edgeCount; i++) {
        int u, v, wt; cin >> u >> v >> wt;
        g.addEdge(u, v, wt);
    }

    TravellingSalesmansProblem tspSolverInstance(g);

    vector<int> ans = tspSolverInstance.getAnswer();

    cout << "PATH:\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "\t";
    }

    cout << "\nPATH COST:\n";
    cout << tspSolverInstance.getCost() << "\n";
}

int main(int argc, char const *argv[])
{
    int testCases; cin >> testCases;
    for (int i = 0; i < testCases; i++) solve(i + 1);
    return 0;
}
