#include <bits/stdc++.h>
using namespace std;

void add(vector<int>& v,int x){
    v.push_back(x);
}

int zbir(vector<int>& v){
    int s=0;
    for(int i=0;i<v.size();i++){
        s+=v[i];
    }
    return s;
}

bool postoji(vector<int>& v,int x){
    for(int i=0;i<v.size();i++){
        if(v[i]==x) return true;
    }
    return false;
}

void bfs(vector<int>& v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
}

void pre_rec(vector<int>& v,int p=0){
    if(p>=v.size()) return;
    cout<<v[p]<<" ";
    pre_rec(v,2*p+1);
    pre_rec(v,2*p+2);
}

void in_rec(vector<int>& v,int p=0){
    if(p>=v.size()) return;
    in_rec(v,2*p+1);
    cout<<v[p]<<" ";
    in_rec(v,2*p+2);
}

void post_rec(vector<int>& v,int p=0){
    if(p>=v.size()) return;
    post_rec(v,2*p+1);
    post_rec(v,2*p+2);
    cout<<v[p]<<" ";
}

void preorder(vector<int>& v){
    if(v.empty()) return;

    stack<int> st;
    st.push(0);

    while(!st.empty()){
        int p=st.top();
        st.pop();

        cout<<v[p]<<" ";

        if(2*p+2<v.size()) st.push(2*p+2);
        if(2*p+1<v.size()) st.push(2*p+1);
    }

    cout<<endl;
}

void inorder(vector<int>& v){
    if(v.empty()) return;

    stack<int> st;
    int p=0;

    while(!st.empty() || p<v.size()){

        while(p<v.size()){
            st.push(p);
            p=2*p+1;
        }

        p=st.top();
        st.pop();

        cout<<v[p]<<" ";

        p=2*p+2;
    }

    cout<<endl;
}

void postorder(vector<int>& v){
    if(v.empty()) return;

    stack<int> st;
    int p=0;
    int last;

    while(!st.empty() || p<v.size()){

        if(p<v.size()){
            st.push(p);
            p=2*p+1;
        }
        else{
            int t=st.top();

            if(2*t+2<v.size() && last!=2*t+2){
                p=2*t+2;
            }
            else{
                cout<<v[t]<<" ";
                last=t;
                st.pop();
            }
        }
    }

    cout<<endl;
}

int main(){

    vector<int> v;

    for(int i=1;i<32;i++){
        add(v,i);
    }

    cout<<zbir(v)<<endl;
    cout<<postoi(v,27)<<endl;

    bfs(v);
    cout<<endl;

    pre_rec(v);
    cout<<endl;

    preorder(v);

    in_rec(v);
    cout<<endl;

    inorder(v);

    postorder(v);
    post_rec(v);
}
