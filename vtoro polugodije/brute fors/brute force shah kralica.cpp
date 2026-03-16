#include <iostream>
#include <vector>
using namespace std;

bool safe(vector<int> &cols, int r, int c) {
    for (int i = 0; i < r; i++)
        if (cols[i] == c || abs(i - r) == abs(cols[i] - c))
            return false;
    return true;
}

void nQueens(int r, int n, vector<int> &cols, int &count) {
    if (r == n) { count++; return; }
    for (int c = 0; c < n; c++) {
        if (safe(cols, r, c)) {
            cols[r] = c;
            nQueens(r + 1, n, cols, count);
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> cols(n);
    int count = 0;
    nQueens(0, n, cols, count);
    cout << count << endl;
}
