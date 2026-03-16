#include <bits/stdc++.h>
using namespace std;

struct Result {
    int sum, left, right;
};

Result max_result(const Result &a, const Result &b, const Result &c) {
    Result best = a;
    if (b.sum > best.sum) best = b;
    if (c.sum > best.sum) best = c;
    return best;
}

Result max_crossing_sum(vector<int> &arr, int l, int m, int r) {
    int sum = 0, best_left_sum = INT_MIN, best_left = m;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > best_left_sum) { best_left_sum = sum; best_left = i; }
    }

    sum = 0;
    int best_right_sum = INT_MIN, best_right = m + 1;
    for (int i = m + 1; i <= r; i++) {
        sum += arr[i];
        if (sum > best_right_sum) { best_right_sum = sum; best_right = i; }
    }

    return {best_left_sum + best_right_sum, best_left, best_right};
}

Result max_subarray(vector<int> &arr, int l, int r) {
    if (l == r) return {arr[l], l, r};
    int m = (l + r)/2;
    return max_result(
        max_subarray(arr, l, m),
        max_subarray(arr, m+1, r),
        max_crossing_sum(arr, l, m, r)
    );
}

int main() {
    int n; cin >> n;
    vector<int> arr(n);
    for (int &x : arr) cin >> x;

    Result res = max_subarray(arr, 0, n-1);
    cout << res.sum << "\n" << res.left << "\n" << res.right << "\n";
}
