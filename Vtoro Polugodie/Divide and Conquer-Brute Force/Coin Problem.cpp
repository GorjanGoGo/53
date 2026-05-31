#include <bits/stdc++.h>
using namespace std;

void add_coin(int coin, vector<pair<int,int>> &v){
    for(auto &p : v){
        if(p.first == coin){
            p.second++;
            return;
        }
    }
}

bool equal_sol(vector<pair<int,int>> &a, vector<pair<int,int>> &b){
    if(a.size() != b.size()) return false;

    for(int i = 0; i < a.size(); i++){
        if(a[i].second != b[i].second)
            return false;
    }
    return true;
}

vector<vector<pair<int,int>>> coin_change(int sum, vector<int> &coins){
    vector<vector<pair<int,int>>> sol;

    vector<pair<int,int>> base;
    for(auto c : coins)
        base.push_back({c,0});

    if(sum == 0){
        sol.push_back(base);
        return sol;
    }

    for(auto c : coins){
        if(sum - c >= 0){
            auto sub = coin_change(sum - c, coins);

            for(auto s : sub){
                add_coin(c, s);
                sol.push_back(s);
            }
        }
    }

    return sol;
}

void remove_dup(vector<vector<pair<int,int>>> &v){
    vector<vector<pair<int,int>>> u;

    for(auto &s : v){
        bool ok = false;

        for(auto &x : u){
            if(equal_sol(s,x)){
                ok = true;
                break;
            }
        }

        if(!ok) u.push_back(s);
    }

    v = u;
}

int count(vector<pair<int,int>> &v){
    int s = 0;
    for(auto &p : v)
        s += p.second;
    return s;
}

int main(){
    int sum;
    vector<int> coins = {1,2,5};

    cout<<"Enter sum: ";
    cin>>sum;

    auto sol = coin_change(sum, coins);

    remove_dup(sol);

    int best = 1e9;
    vector<pair<int,int>> ans;

    for(auto &s : sol){
        int c = count(s);

        if(c < best){
            best = c;
            ans = s;
        }
    }

    cout<<"Best ("<<best<<" coins):\n";

    for(auto &p : ans)
        cout<<"<"<<p.first<<","<<p.second<<"> ";

    cout<<endl;
}