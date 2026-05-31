#include <bits/stdc++.h>
using namespace std;

double dist(const vector<double>& a, const vector<double>& b) {
    double dx = a[0] - b[0];
    double dy = a[1] - b[1];
    double dz = a[2] - b[2];
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double bruteForce(vector<vector<double>>& p, int l, int r) {
    double ans = DBL_MAX;
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            ans = min(ans, dist(p[i], p[j]));
        }
    }
    return ans;
}

double slabClosest(vector<vector<double>>& slab, double d) {
    double ans = d;
    int n = slab.size();

    sort(slab.begin(), slab.end(),
         [](auto &a, auto &b) { return a[1] < b[1]; });

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (slab[j][1] - slab[i][1]) < ans; j++) {
            if (abs(slab[j][2] - slab[i][2]) < ans) {
                ans = min(ans, dist(slab[i], slab[j]));
            }
        }
    }
    return ans;
}

double closestUtil(vector<vector<double>>& px, vector<vector<double>>& py) {
    int n = px.size();
    if (n <= 3)
        return bruteForce(px, 0, n - 1);

    int mid = n / 2;
    double midX = px[mid][0];

    vector<vector<double>> Qx(px.begin(), px.begin() + mid);
    vector<vector<double>> Rx(px.begin() + mid, px.end());

    vector<vector<double>> Qy, Ry;
    for (auto &p : py) {
        if (p[0] <= midX)
            Qy.push_back(p);
        else
            Ry.push_back(p);
    }

    double dl = closestUtil(Qx, Qy);
    double dr = closestUtil(Rx, Ry);
    double d = min(dl, dr);

    vector<vector<double>> slab;
    for (auto &p : py) {
        if (abs(p[0] - midX) < d)
            slab.push_back(p);
    }

    return min(d, slabClosest(slab, d));
}

double closestPair3D(vector<vector<double>>& points) {
    vector<vector<double>> px = points;
    vector<vector<double>> py = points;

    sort(px.begin(), px.end(),
         [](auto &a, auto &b) { return a[0] < b[0]; });

    sort(py.begin(), py.end(),
         [](auto &a, auto &b) { return a[1] < b[1]; });

    return closestUtil(px, py);
}

int main() {
    int n;
    cin >> n;

    vector<vector<double>> points(n, vector<double>(3));
    for (int i = 0; i < n; i++)
        cin >> points[i][0] >> points[i][1] >> points[i][2];

    cout << closestPair3D(points) << endl;
    return 0;
}
