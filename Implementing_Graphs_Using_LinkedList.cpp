#include <iostream>
#include <queue>
using namespace std;

// Node structure for adjacency list
struct Node {
    int vertex;
    Node* next;
};

// Graph class
class Graph {
private:
    int numVertices; // Number of vertices
    Node** adjLists; // Array of adjacency lists
    bool *visited;

public:
    // Constructor
    Graph(int vertices) {
        numVertices = vertices;
        visited = new bool[numVertices];
        adjLists = new Node*[vertices]; // Allocate memory for adjacency lists
        for (int i = 0; i < vertices; i++) {
            adjLists[i] = nullptr; // Initialize each list as empty
        }
        for(int i=0; i<numVertices; i++){
            visited[i] = false;
        }
    }

    // Function to add an edge
    void addEdge(int src, int dest) {
        // Add edge from src to dest
        Node* newNode = new Node{dest, adjLists[src]};
        adjLists[src] = newNode;

        // Add edge from dest to src (for undirected graph)
        newNode = new Node{src, adjLists[dest]};
        adjLists[dest] = newNode;
    }

    // Function to perform BFS traversal
    // void BFS(int startVertex) {
    //     bool* visited = new bool[numVertices]; // Array to track visited vertices
    //     for (int i = 0; i < numVertices; i++) {
    //         visited[i] = false; // Initialize all vertices as unvisited
    //     }

    //     queue<int> q; // Queue for BFS
    //     visited[startVertex] = true; // Mark the starting vertex as visited
    //     q.push(startVertex); // Enqueue the starting vertex

    //     cout << "BFS Traversal starting from vertex " << startVertex << ": ";

    //     while (!q.empty()) {
    //         int currentVertex = q.front(); // Get the front vertex
    //         q.pop(); // Dequeue it

    //         cout << currentVertex << " "; // Print the current vertex

    //         // Traverse all adjacent vertices of the dequeued vertex
    //         Node* temp = adjLists[currentVertex];
    //         while (temp) {
    //             int adjVertex = temp->vertex;

    //             if (!visited[adjVertex]) { // If not visited
    //                 visited[adjVertex] = true; // Mark as visited
    //                 q.push(adjVertex); // Enqueue it
    //             }
    //             temp = temp->next; // Move to the next adjacent vertex
    //         }
    //     }

    //     cout << endl;
    //     delete[] visited; // Clean up memory
    // }


    void DFS(int start) {
        visited[start] = true; // Mark the starting vertex as visited
        cout << start << " ";  // Print the current vertex

        Node* temp = adjLists[start]; // Get the adjacency list for the current vertex
        while (temp) { // Traverse all adjacent vertices
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) { // If not visited
                DFS(adjVertex); // Recur for adjacent vertex
            }
            temp = temp->next; // Move to the next adjacent vertex
        }
    }

    // Destructor to free memory
    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Node* temp = adjLists[i];
            while (temp) {
                Node* nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }
        }
        delete[] adjLists;
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.DFS(0); // Perform BFS starting from vertex 0

    return 0;
}