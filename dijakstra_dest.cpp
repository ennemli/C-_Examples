#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int destination;
  int weight;
};

class Graph {
private:
  int V;
  vector<vector<Edge>> adjacencyList;

public:
  Graph(int vertices) : V(vertices) { adjacencyList.resize(vertices); }

  void addEdge(int source, int dest, int weight) {
    Edge edge = {dest, weight};
    adjacencyList[source].push_back(edge);
    edge = {source, weight};
    adjacencyList[dest].push_back(edge);
  }

  // Find shortest path to all vertices
  vector<int> dijkstraAll(int source) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    vector<int> distances(V, numeric_limits<int>::max());

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
      int u = pq.top().second;
      int dist_u = pq.top().first;
      pq.pop();

      if (dist_u > distances[u])
        continue;

      for (const Edge &edge : adjacencyList[u]) {
        int v = edge.destination;
        int weight = edge.weight;

        if (distances[u] != numeric_limits<int>::max() &&
            distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
          pq.push({distances[v], v});
        }
      }
    }

    return distances;
  }

  // Find shortest path to specific destination
  pair<int, vector<int>> dijkstraDestination(int source, int destination) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    vector<int> distances(V, numeric_limits<int>::max());
    vector<int> parent(V, -1); // To reconstruct the path

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
      int u = pq.top().second;
      int dist_u = pq.top().first;
      pq.pop();

      // Stop if we've reached the destination
      if (u == destination) {
        // Reconstruct path
        vector<int> path;
        for (int v = destination; v != -1; v = parent[v]) {
          path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return {distances[destination], path};
      }

      if (dist_u > distances[u])
        continue;

      for (const Edge &edge : adjacencyList[u]) {
        int v = edge.destination;
        int weight = edge.weight;

        if (distances[u] != numeric_limits<int>::max() &&
            distances[u] + weight < distances[v]) {
          distances[v] = distances[u] + weight;
          parent[v] = u; // Store the parent for path reconstruction
          pq.push({distances[v], v});
        }
      }
    }

    return {numeric_limits<int>::max(), vector<int>()}; // No path found
  }

  void printPath(const vector<int> &path, int distance) {
    if (path.empty()) {
      cout << "No path exists to destination" << endl;
      return;
    }

    cout << "Shortest path (length " << distance << "): ";
    for (size_t i = 0; i < path.size(); i++) {
      cout << path[i];
      if (i < path.size() - 1)
        cout << " -> ";
    }
    cout << endl;
  }
};

int main() {
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

  // Find shortest path from vertex 0 to vertex 5
  auto [distance, path] = g.dijkstraDestination(0, 5);
  g.printPath(path, distance);

  return 0;
}
