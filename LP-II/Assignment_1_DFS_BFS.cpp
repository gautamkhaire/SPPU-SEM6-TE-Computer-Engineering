/*
    Assignment-1
    Implement depth first search algorithm and Breadth First Search algorithm, Use an undirected
    graph and develop a recursive algorithm for searching all the vertices of a graph or tree data
    structure.
*/

#include <bits/stdc++.h>
using namespace std;
class Graph
{
private:
    int vertices;                // No. of Vertices
    int edges;                   // No. of Edges
    vector<vector<int>> adjList; // Adjacency List

public:
    Graph()
    {
        vertices = 0;
        edges = 0;
        adjList.clear();
    }

    void createGraph()
    {
        cout << "Enter number of vertices: ";
        cin >> vertices;
        adjList.resize(vertices + 1);
        cout << "Enter number of edges: ";
        cin >> edges;

        int u, v;
        for (int i = 0; i < edges; i++)
        {
            cout << "Enter sourceNode & destinationNode: ";
            cin >> u >> v;

            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
    }

    void displayGraph()
    {
        for (int node = 0; node < vertices; node++)
        {
            cout << node << "->";
            for (int adjNode : adjList[node])
            {
                cout << adjNode << " ";
            }
            cout << endl;
        }
    }

    void DepthFirstSearch(int node, vector<int> &visited)
    {
        visited[node] = true;
        cout << node << " ";
        
        for (int neighbour : adjList[node])
        {
            if (!visited[neighbour])
            {
                // visited[neighbour] = true;
                DepthFirstSearch(neighbour, visited);
            }
        }
    }
    void DepthFirstSearch()
    {
        vector<int> visited(vertices + 1);
        int startNode;
        cout << "Enter the Starting Vertex of DFS: ";
        cin >> startNode;
        DepthFirstSearch(startNode, visited);

        for (int node = 0; node < vertices; node++) // For Handling Disconnected Components
        {
            if (!visited[node])
            {
                DepthFirstSearch(node, visited);
            }
        }
    }

    void BreadthFirstSearch(int node, vector<int> &visited)
    {
        queue<int> q;
        q.push(node);
        visited[node] = true;

        while (!q.empty())
        {
            int currentNode = q.front();
            q.pop();

            cout << currentNode << " ";

            for (int neighbour : adjList[currentNode])
            {
                if (!visited[neighbour])
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
    void BreadthFirstSearch()
    {
        vector<int> visited(vertices + 1);
        int startNode;
        cout << "Enter the Starting Vertex of BFS: ";
        cin >> startNode;
        BreadthFirstSearch(startNode, visited);

        for (int node = 0; node < vertices; node++) // For Handling Disconnected Components
        {
            if (!visited[node])
            {
                BreadthFirstSearch(node, visited);
            }
        }
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
        cout << " 3. Depth First Search (DFS) Algorithm " << endl;
        cout << " 4. Breadth First Search (BFS) Algorithm " << endl;
        cout << " 5. Exit " << endl;
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
            obj.DepthFirstSearch();
            break;
        case 4:
            obj.BreadthFirstSearch();
            break;
        case 5:
            exit(0);
        }

        cout<<endl;
    }

    return 0;
}