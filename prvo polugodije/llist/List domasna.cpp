#include <bits/stdc++.h>
using namespace std;

class CBHT {
    int n;
    vector<vector<string>> t;

public:
    CBHT(int m){
        n = m;
        t.resize(n);
    }

    int hashLength(const string& s){
        return s.length() % n;
    }

    int hashSum(const string& s){
        int ssum = 0;
        for(int i=0;i<s.length();i++) ssum += s[i];
        return ssum % n;
    }

    int hashFirst(const string& s){
        return (s[0]-'a') % n;
    }

    int hashFirstTwo(const string& s){
        if(s.length()==1) return (s[0]-'a') % n;
        return ((s[0]-'a')*26 + (s[1]-'a')) % n;
    }

    int hash(const string& s, int type){
        if(type==1) return hashLength(s);
        if(type==2) return hashSum(s);
        if(type==3) return hashFirst(s);
        return hashFirstTwo(s);
    }

    void insert(const string& s,int type){
        int h = hash(s,type);
        t[h].push_back(s);
    }

    bool find(const string& s,int type){
        int h = hash(s,type);
        for(int i=0;i<t[h].size();i++)
            if(t[h][i]==s) return true;
        return false;
    }

    void print(){
        for(int i=0;i<n;i++){
            cout << i << ": ";
            for(int j=0;j<t[i].size();j++)
                cout << t[i][j] << " ";
            cout << endl;
        }
    }
};

int main(){
    CBHT h(101);
    h.insert("apple",1);
    h.insert("banana",1);
    h.insert("cat",1);
    h.insert("apple",2);
    h.insert("banana",2);

    cout << h.find("apple",1) << endl;
    cout << h.find("dog",1) << endl;

    h.print();
}
