#include<iostream>
#include<vector>
using namespace std;

class Graph{
    vector<vector<int>> AdjList;
    public:
    Graph(int vertices){
        AdjList.resize(vertices);
    }
    void addEdge(int u, int v){
        AdjList[u].push_back(v);
        AdjList[v].push_back(u);
    }

    void displayGraph() {
    for (int i = 0; i < AdjList.size(); ++i) {
        cout << "Vertex " << i << ":";
        for (int v : AdjList[i]) {
            cout << " -> " << v;
        }
        cout << endl;
    }
}
};

// int main() {
//     Graph g(5); // Create a graph with 5 vertices
//     g.addEdge(0, 1);
//     g.addEdge(0, 4);
//     g.addEdge(1, 2);
//     g.addEdge(1, 3);
//     g.addEdge(1, 4);
//     g.addEdge(2, 3);
//     g.addEdge(3, 4);

//     g.displayGraph(); // Display the graph
//     return 0;
// }