#include <iostream>
#include <vector>
using namespace std;

int n;
int solutions = 0;

bool safe(vector<int>& col, int row, int c) {
    for (int i = 0; i < row; i++) {
        if (col[i] == c || abs(col[i] - c) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solve(vector<int>& col, int row) {
    if (row == n) {
        solutions++;
        return;
    }
    for (int c = 0; c < n; c++) {
        if (safe(col, row, c)) {
            col[row] = c;
            solve(col, row + 1);
        }
    }
}

int main() {
    cin >> n;
    vector<int> col(n);
    solve(col, 0);
    cout << solutions;
}
