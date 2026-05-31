#include <iostream>
#include <vector>
using namespace std;

int maxCrossingSum(vector<int>& a, int l, int m, int r) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--) {
        sum += a[i];
        left_sum = max(left_sum, sum);
    }
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= r; i++) {
        sum += a[i];
        right_sum = max(right_sum, sum);
    }
    return left_sum + right_sum;
}

int maxSubarray(vector<int>& a, int l, int r) {
    if (l == r) return a[l];
    int m = (l + r) / 2;
    return max(  max(maxSubarray(a, l, m), maxSubarray(a, m + 1, r)), maxCrossingSum(a, l, m, r));
}

int main() {
    int n;
    cin>>n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    cout << maxSubarray(a, 0, n - 1);
}
