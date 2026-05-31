#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<int> dijkstra(int start, const vector<vector<pair<int,int>>> &g) {
    int n = g.size();
    vector<int> d(n, INT_MAX);
    d[start] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, start});

    while (pq.size()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (dist != d[u]) continue;

        for (auto [v, w] : g[u]) {
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }

    return d;
}

int main() {
    vector<vector<pair<int,int>>> g(6);
    g[0] = {{5,4}, {1,2}};
    g[1] = {{0,2}, {3,9}};
    g[2] = {{3,5}};
    g[3] = {{4,1}, {2,5}, {1,9}};
    g[4] = {{3,1}};
    g[5] = {{0,4}};

    auto res = dijkstra(0, g);

    for (int i = 0; i < res.size(); i++) {
        cout << i << " -> " << res[i] << '\n';
    }

    return 0;
}
