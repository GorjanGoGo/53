#include <iostream>
using namespace std;

pair<int,int> toMatrix(pair<char,int> pos) {
    return {pos.first-'a', pos.second-1};
}

int countAvailable(int board[8][8], int x, int y) {
    int dx[8]={-2,-2,2,2,-1,-1,1,1};
    int dy[8]={-1,1,-1,1,-2,2,-2,2};
    int cnt=0;
    for (int i=0;i<8;i++) {
        int nx=x+dx[i], ny=y+dy[i];
        if (nx>=0 && nx<8 && ny>=0 && ny<8 && board[nx][ny]==0)
            cnt++;
    }
    return cnt;
}

void moveKnight(int board[8][8], int x, int y) {
    static int step=2;
    int dx[8]={-2,-2,2,2,-1,-1,1,1};
    int dy[8]={-1,1,-1,1,-2,2,-2,2};
    int minAvail=9;
    pair<int,int> nextMove;

    for (int i=0;i<8;i++) {
        int nx=x+dx[i], ny=y+dy[i];
        if (nx>=0 && nx<8 && ny>=0 && ny<8 && board[nx][ny]==0) {
            int avail=countAvailable(board,nx,ny);
            if (avail<minAvail) {
                minAvail=avail;
                nextMove={nx,ny};
            }
        }
    }

    board[nextMove.first][nextMove.second]=step++;
    if (step<=64)
        moveKnight(board,nextMove.first,nextMove.second);
}

int main() {
    pair<char,int> startPos;
    cin>>startPos.first>>startPos.second;
    int board[8][8]={0};
    pair<int,int> start=toMatrix(startPos);
    board[start.first][start.second]=1;
    moveKnight(board,start.first,start.second);

    for (int i=0;i<8;i++) {
        for (int j=0;j<8;j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
}
