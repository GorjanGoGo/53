#include <bits/stdc++.h>
using namespace std;

const int N = 8;
int board[N][N];
int dx[8] = {2,2,1,1,-1,-1,-2,-2};
int dy[8] = {1,-1,2,-2,2,-2,1,-1};

bool inside(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1;
}

bool solve(int x, int y, int moveNo) {
    if (moveNo == N * N) return true;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (inside(nx, ny)) {
            board[nx][ny] = moveNo;
            if (solve(nx, ny, moveNo + 1)) return true;
            board[nx][ny] = -1;
        }
    }
    return false;
}

int main() {
    int sx, sy;
    cin >> sx >> sy;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }
    board[sx][sy] = 0;
    
    if (solve(sx, sy, 1)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Nema reshenie";
    }
}
