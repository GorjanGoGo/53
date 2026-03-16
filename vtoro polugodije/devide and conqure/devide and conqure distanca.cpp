#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y, z;
};

double dist2(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

double brute(vector<Point> &pts, int l, int r) {
    double best = 1e18;
    for (int i = l; i <= r; i++)
        for (int j = i + 1; j <= r; j++)
            best = min(best, dist2(pts[i], pts[j]));
    return best;
}

double closest(vector<Point> &pts, int l, int r) {
    if (r - l <= 3) return brute(pts, l, r);
    int mid = (l + r) / 2;
    double dl = closest(pts, l, mid);
    double dr = closest(pts, mid + 1, r);
    double d = min(dl, dr);

    double midx = pts[mid].x;
    vector<Point> strip;
    for (int i = l; i <= r; i++)
        if ((pts[i].x - midx)*(pts[i].x - midx) < d)
            strip.push_back(pts[i]);

    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size(); j++)
            d = min(d, dist2(strip[i], strip[j]));

    return d;
}

int main() {
    int n;
    cin >> n;
    vector<Point> pts(n);
    for (int i = 0; i < n; i++)
        cin >> pts[i].x >> pts[i].y >> pts[i].z;

    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b){ return a.x < b.x; });

    cout << sqrt(closest(pts, 0, n - 1)) << endl;
}
