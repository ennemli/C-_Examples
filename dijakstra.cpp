#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
  int destination;
  int weight;
};

class Graph {
private:
  int V; // Number of vertices
  vector<vector<Edge>> adjacencyList;

public:
  Graph(int vertices) : V(vertices) { adjacencyList.resize(vertices); }

  // Add an edge to the graph
  void addEdge(int source, int dest, int weight) {
    Edge edge = {dest, weight};
    adjacencyList[source].push_back(edge);
    // For undirected graph, add the reverse edge
    edge = {source, weight};
    adjacencyList[dest].push_back(edge);
  }

  // Implement Dijkstra's algorithm
  vector<int> dijkstra(int source) {
    // Priority queue to store vertices and their distances
    // pair: (distance, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    // Vector to store distances from source to all vertices
    vector<int> distances(V, numeric_limits<int>::max());

    // Distance to source is 0
    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
      // Get vertex with minimum distance
      int u = pq.top().second;
      int dist_u = pq.top().first;
      pq.pop();

      // If this distance is greater than what we have, skip
      if (dist_u > distances[u])
        continue;

      // Check all adjacent vertices
      for (const Edge &edge : adjacencyList[u]) {
        int v = edge.destination;
        int weight = edge.weight;

        // If we found a shorter path to v through u
        if (distances[u] != numeric_limits<int>::max() &&
            distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
          pq.push({distances[v], v});
        }
      }
    }

    return distances;
  }

  // Utility function to print the distances
  void printDistances(const vector<int> &distances) {
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
      cout << i << "\t";
      if (distances[i] == numeric_limits<int>::max())
        cout << "INF";
      else
        cout << distances[i];
      cout << endl;
    }
  }
};

// Example usage
int main() {
  // Create a graph with 6 vertices
  Graph g(6);

  // Add edges
  g.addEdge(0, 1, 14);
  g.addEdge(0, 2, 3);
  g.addEdge(0, 3, 10);
  g.addEdge(1, 2, 7);
  g.addEdge(1, 4, 11);
  g.addEdge(1, 5, 20);
  g.addEdge(2, 3, 6);
  g.addEdge(2, 4, 15);
  g.addEdge(3, 4, 18);
  g.addEdge(3, 5, 16);
  g.addEdge(4, 5, 17);

  // Calculate shortest paths from vertex 0
  vector<int> distances = g.dijkstra(0);

  // Print the results
  g.printDistances(distances);

  return 0;
}
