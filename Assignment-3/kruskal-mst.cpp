#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
  int src, dest, weight;
};

// Function to compare two edges based on their weights
bool compareEdges(const Edge& e1, const Edge& e2) {
  return e1.weight < e2.weight;
}

// Function to find the parent node of a vertex in the disjoint-set data structure
int findParent(vector<int>& parent, int u) {
  if (parent[u] != u) {
    parent[u] = findParent(parent, parent[u]);
  }
  return parent[u];
}

// Function to perform union operation on two disjoint sets
void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
  int xroot = findParent(parent, x);
  int yroot = findParent(parent, y);

  // Attach the smaller tree under the root of the larger tree
  if (rank[xroot] < rank[yroot]) {
    parent[xroot] = yroot;
  } else if (rank[xroot] > rank[yroot]) {
    parent[yroot] = xroot;
  } else {
    // If ranks are same, then increment rank of one root
    parent[yroot] = xroot;
    rank[xroot]++;
  }
}

// Function to construct and return the minimum spanning tree using Kruskal's algorithm
vector<Edge> KruskalsMST(vector<Edge>& edges, int V) {
  vector<Edge> result; // Stores edges in the MST
  vector<int> parent(V); // Stores parent of each vertex
  vector<int> rank(V, 0); // Stores rank of each vertex for efficient union-find

  // Sort edges in non-decreasing order of their weight
  sort(edges.begin(), edges.end(), compareEdges);

  // Initialize all vertices as single-vertex sets
  for (int i = 0; i < V; i++) {
    parent[i] = i;
  }

  int i = 0; // Index used to pick next edge
  while (result.size() < V - 1) {
    // Pick next edge from the sorted list
    Edge next_edge = edges[i++];

    // Check if the selected edge forms a cycle
    int x = findParent(parent, next_edge.src);
    int y = findParent(parent, next_edge.dest);

    if (x != y) {
      // Add the edge to the result as it doesn't form a cycle
      result.push_back(next_edge);
      // Perform union operation to merge sets
      unionSets(parent, rank, x, y);
    }
  }

  return result;
}

int main() {
  // Sample graph edges
  vector<Edge> edges = {
    {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}, {4, 5, 3}, {5, 6, 1}
  };
  int V = 7; // Number of vertices in the graph

  // Find MST using Kruskal's algorithm
  vector<Edge> mst = KruskalsMST(edges, V);

  cout << "Edges in the constructed MST: \n";
  for (Edge edge : mst) {
    cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
  }

  return 0;
}
