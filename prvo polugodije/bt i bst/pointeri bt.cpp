#include <iostream>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

class Btree {
    int val;
    Btree* left;
    Btree* right;
public:
    Btree() {
        val=INT_MIN;
        left=nullptr;
        right=nullptr;
    }
    ~Btree() {}
    void insert(int val) {
        if (this->val==INT_MIN) {
            this->val=val;
            return;
        }
        queue<Btree*> q;
        q.push(this);
        Btree* curr=q.front();
        while (curr->left && curr->right) {
            q.pop();
            q.push(curr->left);
            q.push(curr->right);
            curr=q.front();
        }
        if (!curr->left) {
            curr->left=new Btree();
            curr->left->val=val;
        }
        else if (!curr->right) {
            curr->right=new Btree();
            curr->right->val=val;
        }
    }
    bool find(int val) {
        if (this->val == INT_MIN)
            return false;
        queue<Btree*> q;
        q.push(this);
        while (!q.empty()) {
            Btree* curr=q.front();
            q.pop();
            if (curr->val==val) {
                return true;
            }
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        return false;
    }
    int sum() {
        int sum=0;
        queue<Btree*> q;
        q.push(this);
        while (!q.empty()) {
            Btree* curr=q.front();
            sum+=curr->val;
            q.pop();
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        return sum;
    }
    void BFS () {
        if (this->val == INT_MIN) return;
        queue<Btree*> q;
        q.push(this);
        while (!q.empty()) {
            Btree* curr = q.front();
            q.pop();
            cout << curr->val << " ";
            if (curr->left != nullptr)
                q.push(curr->left);
            if (curr->right != nullptr)
                q.push(curr->right);
        }
        cout<<endl;
    }
    //DFS with recursion
    void preorder_rec() {
        if (this->val==INT_MIN) return;
        cout<<this->val<<" ";
        if (this->left) {
            this->left->preorder_rec();
        }
        if (this->right) {
            this->right->preorder_rec();
        }
    }
    void inorder_rec() {
        if (this->val==INT_MIN) return;
        if (this->left) {
            this->left->inorder_rec();
        }
        cout<<this->val<<" ";
        if (this->right) {
            this->right->inorder_rec();
        }
    }
    void postorder_rec() {
        if (this->val==INT_MIN) return;
        if (this->left) {
            this->left->postorder_rec();
        }
        if (this->right) {
            this->right->postorder_rec();
        }
        cout<<this->val<<" ";
    }
    //DFS without recursion
    void preorder() {
        if (this->val==INT_MIN) return;
        stack<Btree*>s;
        s.push(this);
        while (!s.empty()) {
            Btree* curr=s.top();
            s.pop();
            cout<<curr->val<<" ";
            if (curr->right) {
                s.push(curr->right);
            }
            if (curr->left) {
                s.push(curr->left);
            }
        }
        cout<<endl;
    }
    void inorder() {
        if (this->val==INT_MIN) return;
        stack<Btree*> s;
        Btree* curr=this;
        while (!s.empty() || curr) {
            while (curr) {
                s.push(curr);
                curr=curr->left;
            }
            curr=s.top();
            cout<<curr->val<<" ";
            s.pop();
            curr=curr->right;
        }
        cout<<endl;
    }
    void postorder() {
        if (val == INT_MIN) return;
        stack<Btree*> s;
        Btree* curr = this;
        Btree* lastVisited = nullptr;
        while (curr || !s.empty()) {
            if (curr) {
                s.push(curr);
                curr = curr->left;
            }
            else {
                Btree* peekNode = s.top();
                if (peekNode->right && lastVisited!=peekNode->right) {
                    curr=peekNode->right;
                }
                else {
                    cout<<peekNode->val<<" ";
                    lastVisited = peekNode;
                    s.pop();
                }
            }
        }
        cout<<endl;
    }
};

int main() {
    Btree t;
    for (int i=1;i<32;i++) {
        t.insert(i);
    }
    cout<<t.find(3)<<endl;
    cout<<t.sum()<<endl;
    t.BFS();
    t.preorder_rec();
    cout<<endl;
    t.preorder();
    t.inorder_rec();
    cout<<endl;
    t.inorder();
    t.postorder_rec();
    cout<<endl;
    t.postorder();
    return 0;
}