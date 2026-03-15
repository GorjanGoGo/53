#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
    void unionSets(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa != pb)
            parent[pb] = pa;
    }
};

class UnionFindSize {
    vector<int> parent, sz;
public:
    UnionFindSize(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
    void unionSets(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return;
        if (sz[pa] < sz[pb]) {
            parent[pa] = pb;
            sz[pb] += sz[pa];
        } else {
            parent[pb] = pa;
            sz[pa] += sz[pb];
        }
    }
};

class UnionFindRank {
    vector<int> parent, rank;
public:
    UnionFindRank(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }
    void unionSets(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return;
        if (rank[pa] < rank[pb])
            parent[pa] = pb;
        else if (rank[pa] > rank[pb])
            parent[pb] = pa;
        else {
            parent[pb] = pa;
            rank[pa]++;
        }
    }
};

class UnionFindRankPC {
    vector<int> parent, rank;
public:
    UnionFindRankPC(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unionSets(int a, int b) {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb) return;
        if (rank[pa] < rank[pb])
            parent[pa] = pb;
        else if (rank[pa] > rank[pb])
            parent[pb] = pa;
        else {
            parent[pb] = pa;
            rank[pa]++;
        }
    }
};

int main() {
    int n = 7;
    UnionFind uf(n);
    UnionFindSize ufSize(n);
    UnionFindRank ufRank(n);
    UnionFindRankPC ufRankPC(n);
    uf.unionSets(0, 1);
    uf.unionSets(1, 2);
    ufSize.unionSets(0, 1);
    ufSize.unionSets(1, 2);
    ufRank.unionSets(0, 1);
    ufRank.unionSets(1, 2);
    ufRankPC.unionSets(0, 1);
    ufRankPC.unionSets(1, 2);
    cout << (uf.find(0) == uf.find(2)) << endl;
    cout << (ufSize.find(0) == ufSize.find(2)) << endl;
    cout << (ufRank.find(0) == ufRank.find(2)) << endl;
    cout << (ufRankPC.find(0) == ufRankPC.find(2)) << endl;
    return 0;
}
