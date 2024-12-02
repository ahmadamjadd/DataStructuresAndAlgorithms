#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjMatrix; // Adjacency matrix
    int numVertices;              // Number of vertices

public:
    // Constructor to initialize the graph with given vertices
    Graph(int vertices) {
        numVertices = vertices;
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    // Add an edge to the graph
    void addEdge(int u, int v, bool isDirected = false) {
        if (u >= numVertices || v >= numVertices || u < 0 || v < 0) {
            cout << "Invalid edge!\n";
            return;
        }
        adjMatrix[u][v] = 1;
        if (!isDirected) {
            adjMatrix[v][u] = 1;
        }
    }

    // Display the adjacency matrix
    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // BFS Traversal
    void bfs(int start) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[node][j] == 1 && !visited[j]) {
                    visited[j] = true;
                    q.push(j);
                }
            }
        }
        cout << endl;
    }

    // DFS Traversal
    void dfsUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[node][j] == 1 && !visited[j]) {
                dfsUtil(j, visited);
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(numVertices, false);
        cout << "DFS Traversal: ";
        dfsUtil(start, visited);
        cout << endl;
    }

    // Search for a node
    bool searchNode(int node) {
        if (node >= 0 && node < numVertices) {
            return true;
        }
        return false;
    }

    // Delete a node
    void deleteNode(int node) {
        if (node < 0 || node >= numVertices) {
            cout << "Invalid node!\n";
            return;
        }

        // Remove connections from the adjacency matrix
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[node][i] = 0;
            adjMatrix[i][node] = 0;
        }

        cout << "Node " << node << " deleted.\n";
    }
};

int main() {
    int vertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

    Graph g(vertices);

    while (true) {
        cout << "\nGraph Operations:\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Graph\n";
        cout << "3. BFS\n";
        cout << "4. DFS\n";
        cout << "5. Search Node\n";
        cout << "6. Delete Node\n";
        cout << "7. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int u, v;
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
        } else if (choice == 2) {
            g.display();
        } else if (choice == 3) {
            int start;
            cout << "Enter starting node for BFS: ";
            cin >> start;
            g.bfs(start);
        } else if (choice == 4) {
            int start;
            cout << "Enter starting node for DFS: ";
            cin >> start;
            g.dfs(start);
        } else if (choice == 5) {
            int node;
            cout << "Enter node to search: ";
            cin >> node;
            if (g.searchNode(node)) {
                cout << "Node " << node << " exists in the graph.\n";
            } else {
                cout << "Node " << node << " does not exist in the graph.\n";
            }
        } else if (choice == 6) {
            int node;
            cout << "Enter node to delete: ";
            cin >> node;
            g.deleteNode(node);
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
