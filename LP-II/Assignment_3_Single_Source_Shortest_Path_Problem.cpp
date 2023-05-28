#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int vertices;
    int edges;
    unordered_map<int, vector<pair<int, int>>> adjList; // Adjacency List

public:
    Graph()
    {
        this->vertices = 0;
        this->edges = 0;
        this->adjList.clear();
    }

    void createGraph()
    {
        cout << "Enter number of vertices: ";
        cin >> vertices;
        cout << "Enter number of edges: ";
        cin >> edges;

        int u, v, edgeWeight;
        for (int i = 0; i < edges; i++)
        {
            cout << "Enter sourceNode, destinationNode, edgeWeight : ";
            cin >> u >> v >> edgeWeight;

            // Undirected Graph
            adjList[u].push_back({v, edgeWeight});
            adjList[v].push_back({u, edgeWeight});
        }
    }

    void displayGraph()
    {
        for (int node = 0; node < vertices; node++)
        {
            cout << node << " -> ";
            for (pair<int, int> &neighbour : adjList[node])
            {
                cout << "{" << neighbour.first << "," << neighbour.second << "} ";
            }
            cout << endl;
        }
    }

    void dijkstra()
    {
        int sourceNode, destinationNode;
        cout << "Enter the sourceNode & destinationNode : ";
        cin >> sourceNode >> destinationNode;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-Heap { distance,Node }
        vector<int> distance(vertices, INT_MAX);
        vector<int> parent(vertices);
        for (int node = 0; node < vertices; node++)
        {
            parent[node] = node;
        }

        distance[sourceNode] = 0;
        pq.push({0, sourceNode});

        while (!pq.empty())
        {
            pair<int, int> current = pq.top();
            pq.pop();

            int currentDistance = current.first;
            int currentNode = current.second;

            for (pair<int, int> &neighbour : adjList[currentNode])
            {
                int adjacentNode = neighbour.first;
                int edgeWeight = neighbour.second;

                if ((currentDistance + edgeWeight) < distance[adjacentNode])
                {
                    distance[adjacentNode] = currentDistance + edgeWeight;
                    pq.push({distance[adjacentNode], adjacentNode});
                    parent[adjacentNode] = currentNode;
                }
            }
        }

        cout << "Shortest Path from SourceNode: " << sourceNode << " to DestinationNode: " << destinationNode << endl;
        int node = destinationNode;
        vector<int> path;
        while (node != parent[node])
        {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(node);
        reverse(path.begin(), path.end());
        for (int node : path)
            cout << node << " -> ";
    }
};
int main()
{
    Graph obj;
    int option;
    while (true)
    {
        cout << " -------------------- MENU -------------------- " << endl;
        cout << " 1. Create a Graph " << endl;
        cout << " 2. Display a Graph " << endl;
        cout << " 3. Dijkstra's Algorithm (Single Source Shortest Path Algorithm) " << endl;
        cout << " 4. Exit " << endl;
        cout << " Enter the option: ";
        cin >> option;

        switch (option)
        {
        case 1:
            obj.createGraph();
            break;
        case 2:
            obj.displayGraph();
            break;
        case 3:
            obj.dijkstra();
            break;
        case 4:
            exit(0);
        default:
            cout << " Invalid Option. Please Enter a Valid Option. " << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}