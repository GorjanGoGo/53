#include <bits/stdc++.h>
using namespace std;

class UF {
    vector<int> par;
public:
    UF(int n) {
        par.resize(n);
        for(int i=0;i<n;i++) par[i]=i;
    }
    int getRoot(int x){
        while(par[x]!=x) x=par[x];
        return x;
    }
    void join(int a,int b){
        int ra=getRoot(a);
        int rb=getRoot(b);
        if(ra!=rb) par[rb]=ra;
    }
};

class UFSize {
    vector<int> par, sz;
public:
    UFSize(int n){
        par.resize(n);
        sz.resize(n,1);
        for(int i=0;i<n;i++) par[i]=i;
    }
    int getRoot(int x){
        while(par[x]!=x) x=par[x];
        return x;
    }
    void join(int a,int b){
        int ra=getRoot(a);
        int rb=getRoot(b);
        if(ra==rb) return;
        if(sz[ra]<sz[rb]){
            par[ra]=rb;
            sz[rb]+=sz[ra];
        } else {
            par[rb]=ra;
            sz[ra]+=sz[rb];
        }
    }
};

class UFRank {
    vector<int> par, rk;
public:
    UFRank(int n){
        par.resize(n);
        rk.resize(n,0);
        for(int i=0;i<n;i++) par[i]=i;
    }
    int getRoot(int x){
        while(par[x]!=x) x=par[x];
        return x;
    }
    void join(int a,int b){
        int ra=getRoot(a);
        int rb=getRoot(b);
        if(ra==rb) return;
        if(rk[ra]<rk[rb]) par[ra]=rb;
        else if(rk[ra]>rk[rb]) par[rb]=ra;
        else{
            par[rb]=ra;
            rk[ra]++;
        }
    }
};

class UFRankPC {
    vector<int> par, rk;
public:
    UFRankPC(int n){
        par.resize(n);
        rk.resize(n,0);
        for(int i=0;i<n;i++) par[i]=i;
    }
    int getRoot(int x){
        if(par[x]!=x) par[x]=getRoot(par[x]);
        return par[x];
    }
    void join(int a,int b){
        int ra=getRoot(a);
        int rb=getRoot(b);
        if(ra==rb) return;
        if(rk[ra]<rk[rb]) par[ra]=rb;
        else if(rk[ra]>rk[rb]) par[rb]=ra;
        else{
            par[rb]=ra;
            rk[ra]++;
        }
    }
};

int main(){
    int n=7;
    UF uf(n);
    UFSize ufs(n);
    UFRank ufr(n);
    UFRankPC ufrpc(n);

    uf.join(0,1); uf.join(1,2);
    ufs.join(0,1); ufs.join(1,2);
    ufr.join(0,1); ufr.join(1,2);
    ufrpc.join(0,1); ufrpc.join(1,2);

    cout<<(uf.getRoot(0)==uf.getRoot(2))<<endl;
    cout<<(ufs.getRoot(0)==ufs.getRoot(2))<<endl;
    cout<<(ufr.getRoot(0)==ufr.getRoot(2))<<endl;
    cout<<(ufrpc.getRoot(0)==ufrpc.getRoot(2))<<endl;

    return 0;
}
