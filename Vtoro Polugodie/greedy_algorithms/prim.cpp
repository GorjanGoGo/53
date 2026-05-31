#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int prim(const vector<vector<pair<int,int>>> &g) {
    int n = g.size();
    vector<bool> used(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0, 0});
    int total = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (used[u]) continue;

        used[u] = true;
        total += w;

        for (auto [v, cost] : g[u]) {
            if (!used[v]) {
                pq.push({cost, v});
            }
        }
    }

    return total;
}

int main() {
    vector<vector<pair<int,int>>> g(5);
    g[0] = {{1,5}};
    g[1] = {{2,1}, {3,2}};
    g[2] = {{4,1}};
    g[4] = {{3,-1}};

    cout << prim(g);

    return 0;
}
