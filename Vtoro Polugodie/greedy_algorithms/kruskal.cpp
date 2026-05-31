#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p;

    DSU(int n) : p(n, -1) {}

    int get(int x) {
        return p[x] < 0 ? x : p[x] = get(p[x]);
    }

    bool join(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return false;

        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int kruskal(vector<vector<pair<int,int>>> &g) {
    vector<tuple<int,int,int>> e;

    for (int u = 0; u < g.size(); u++) {
        for (auto [v, w] : g[u]) {
            if (u < v) e.push_back({w, u, v});
        }
    }

    sort(e.begin(), e.end());

    DSU dsu(g.size());
    int sum = 0;

    for (auto [w, u, v] : e) {
        if (dsu.join(u, v)) {
            sum += w;
        }
    }

    return sum;
}

int main() {
    vector<vector<pair<int,int>>> g(5);
    g[0] = {{1,5}};
    g[1] = {{2,1}, {3,2}};
    g[2] = {{4,1}};
    g[4] = {{3,-1}};

    cout << kruskal(g);

    return 0;
}
