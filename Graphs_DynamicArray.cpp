#include <iostream>
#include <queue>
using namespace std;

class Graph {
private:
    int vertices;
    int** matrix;

public:
    Graph(int vertices) {
        this->vertices = vertices;
        matrix = new int*[vertices];
        for (int i = 0; i < vertices; i++) {
            matrix[i] = new int[vertices];
        }

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                matrix[i][j] = 0;
            }
        }
    }

    void add(int u, int v, bool isDirected = false) {
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            matrix[u][v] = 1;
            if (!isDirected) {
                matrix[v][u] = 1;
            }
        } else {
            cout << "Vertices are out of range!" << endl;
        }
    }

    void del(int u, int v, bool isDirected = false) {
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            if (matrix[u][v] == 0) {
                cout << "No edge present here!" << endl;
            } else {
                matrix[u][v] = 0;
                if (!isDirected) {
                    matrix[v][u] = 0; // Corrected here
                }
            }
        } else {
            cout << "Invalid Vertices" << endl;
        }
    }

    void BFS(int start) {
        int* visited = new int[vertices](); // Initialize with 0
        visited[start] = 1;
        queue<int> explore;
        explore.push(start);
        while (!explore.empty()) {
            int vertex = explore.front();
            explore.pop();
            cout << vertex << " ";
            for (int i = 0; i < vertices; i++) {
                if (matrix[vertex][i] == 1 && visited[i] == 0) {
                    visited[i] = 1;
                    explore.push(i);
                }
            }
        }
        delete[] visited; // Free memory
    }

    void DFS(int start, int visited[], int n) {
        visited[start] = 1;  // Mark the current vertex as visited
        cout << start << " "; // Process the current vertex

        // Explore all adjacent vertices
        for (int i = 0; i < n; i++) {
            if (matrix[start][i] == 1 && !visited[i]) { // Check for edge and unvisited vertex
                DFS(i, visited, n);
            }
        }
    }
};

int main() {
    Graph G(5);
    G.add(0, 1);
    G.add(0, 2);
    G.add(0, 3);
    cout << "BFS: ";
    G.BFS(0);
    cout << endl;

    int visited[5] = {0}; // Initialize all elements to 0
    cout << "DFS: ";
    G.DFS(0, visited, 5);
    cout << endl;

    return 0;
}
