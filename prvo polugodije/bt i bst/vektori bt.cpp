#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void insert(vector<int>& tree, int val) {
    tree.push_back(val);
}
int sum(vector<int>& tree) {
    int sum=0;
    for (int i=0;i<tree.size();i++) {
        sum+=tree[i];
    }
    return sum;
}
bool find(vector<int>& tree,int val) {
    for (int i=0;i<tree.size();i++) {
        if (val==tree[i]) return true;
    }
    return false;
}
void BFS(vector<int>& tree) {
    for (int i=0;i<tree.size();i++) {
        cout<<tree[i]<<" ";
    }
}
//DFS with recursion
void preorder_rec(vector<int>& tree,int i=0) {
    if (i>=tree.size()) return;
    cout<<tree[i]<<" ";
    preorder_rec(tree,2*i+1);
    preorder_rec(tree,2*i+2);
}
void inorder_rec(vector<int>& tree,int i=0) {
    if (i>=tree.size()) return;
    inorder_rec(tree,2*i+1);
    cout<<tree[i]<<" ";
    inorder_rec(tree,2*i+2);
}
void postorder_rec(vector<int>& tree,int i=0) {
    if (i>=tree.size()) return;
    postorder_rec(tree,2*i+1);
    postorder_rec(tree,2*i+2);
    cout<<tree[i]<<" ";
}
//DFS without recursion
void preorder(vector<int>& tree) {
    if (tree.empty()) return;
    stack<int>s;
    s.push(0);
    while (!s.empty()) {
        int i=s.top();
        cout<<tree[i]<<" ";
        s.pop();
        if (2*i+2<tree.size()) {
            s.push(2*i+2);
        }
        if (2*i+1<tree.size()) {
            s.push(2*i+1);
        }
    }
    cout<<endl;
}
void inorder(vector<int>& tree) {
    if (tree.empty()) return;
    stack<int>s;
    int i=0;
    while (!s.empty() || i<tree.size()) {
        while (i<tree.size()) {
            s.push(i);
            i=2*i+1;
        }
        i=s.top();
        cout<<tree[i]<<" ";
        s.pop();
        i=2*i+2;
    }
    cout<<endl;
}
void postorder(vector<int>& tree) {
    if (tree.empty()) return;
    stack<int>s;
    int i=0;
    int lastVisited;
    while (!s.empty() || i<tree.size()) {
        if (i<tree.size()) {
            s.push(i);
            i=2*i+1;
        }
        else {
            int peekNode=s.top();
            if (2*peekNode+2<tree.size() && lastVisited!=2*peekNode+2) {
                i=2*peekNode+2;
            }
            else {
                cout<<tree[peekNode]<<" ";
                lastVisited=peekNode;
                s.pop();
            }
        }
    }
    cout<<endl;
}
int main() {
    /* kaj binarno drvo pretstaveno so vektor se dvizhime spored indeksite, vektorot gi jazlite samo
       pr. so indeks 0 ni e root, so 1 i 2 ni se decata vo prviot sloj i tn.
       deca na eden jazol se odreduvaat taka sto:
       1. indeks na levo dete: 2*i+1
       2. indeks na desno dete: 2*i+2
       kade i ni e indeksot na jazolot na koj se naogjame
     */
    vector<int> tree;
    for (int i=1;i<32;i++) {
        insert(tree,i);
    }
    cout<<sum(tree)<<endl;
    cout<<find(tree,27)<<endl;
    BFS(tree);
    cout<<endl;
    preorder_rec(tree);
    cout<<endl;
    preorder(tree);
    inorder_rec(tree);
    cout<<endl;
    inorder(tree);
    postorder(tree);
    postorder_rec(tree);
}