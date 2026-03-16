#include <bits/stdc++.h>
using namespace std;

void increaseCoin(int coin, vector<pair<int,int>> &combination) {
    for (auto &p : combination) {
        if (p.first == coin) {
            p.second++;
            return;
        }
    }
}

bool sameCombination(const vector<pair<int,int>> &a, const vector<pair<int,int>> &b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i].second != b[i].second) return false;
    }
    return true;
}

vector<vector<pair<int,int>>> getCoinCombinations(int amount, vector<int> &coins) {
    vector<vector<pair<int,int>>> result;
    vector<pair<int,int>> zeroCount;
    for (int c : coins) zeroCount.push_back({c, 0});

    if (amount == 0) {
        result.push_back(zeroCount);
    } else {
        for (int c : coins) {
            if (amount - c >= 0) {
                auto sub = getCoinCombinations(amount - c, coins);
                for (auto comb : sub) {
                    increaseCoin(c, comb);
                    result.push_back(comb);
                }
            }
        }
    }
    return result;
}

void removeDuplicates(vector<vector<pair<int,int>>> &solutions) {
    vector<vector<pair<int,int>>> unique;
    for (auto &comb : solutions) {
        bool found = false;
        for (auto &u : unique) {
            if (sameCombination(comb, u)) {
                found = true;
                break;
            }
        }
        if (!found) unique.push_back(comb);
    }
    solutions = unique;
}

int totalCoins(const vector<pair<int,int>> &comb) {
    int sum = 0;
    for (auto &p : comb) sum += p.second;
    return sum;
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount;
    cout << "Enter change sum: ";
    cin >> amount;

    auto solutions = getCoinCombinations(amount, coins);
    removeDuplicates(solutions);

    int minCoins = INT_MAX;
    vector<pair<int,int>> bestSolution;

    for (auto &comb : solutions) {
        int cnt = totalCoins(comb);
        if (cnt < minCoins) {
            minCoins = cnt;
            bestSolution = comb;
        }
    }

    cout << "\nOptimal solution (" << minCoins << " coins):\n";
    for (auto &p : bestSolution) {
        cout << "<" << p.first << "," << p.second << "> ";
    }
    cout << endl;

    return 0;
}
