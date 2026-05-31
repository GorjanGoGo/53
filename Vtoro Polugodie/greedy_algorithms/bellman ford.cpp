#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> bellman_ford(vector<vector<pair<int, int>>> &graph, int source) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX);
    distances[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int node = 0; node < n; node++) {
            for (auto &edge : graph[node]) {
                int neighbour = edge.first;
                int weight = edge.second;

                if (distances[node] != INT_MAX && distances[node] + weight < distances[neighbour]) {
                    distances[neighbour] = distances[node] + weight;
                }
            }
        }
    }

    for (int node = 0; node < n; node++) {
        for (auto &edge : graph[node]) {
            int neighbour = edge.first;
            int weight = edge.second;

            if (distances[node] != INT_MAX && distances[node] + weight < distances[neighbour]) {
                return vector<int>{-1};
            }
        }
    }

    return distances;
}

int main() {
    vector<vector<pair<int, int>>> graph(5);
    graph[0] = {{1, 5}};
    graph[1] = {{2, 1}, {3, 2}};
    graph[2] = {{4, 1}};
    graph[4] = {{3, -1}};

    vector<int> dist = bellman_ford(graph, 0);

    for (int i = 0; i < dist.size(); i++) {
        cout << i << ": " << dist[i] << '\n';
    }

    return 0;
}
