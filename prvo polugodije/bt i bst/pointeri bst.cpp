#include <iostream>
#include <climits>
#include <queue>
#include <stack>
using namespace std;

class BST {
    int val;
    BST* left;
    BST* right;
public:
    BST() {
        val=INT_MIN;
        left=nullptr;
        right=nullptr;
    }
    ~BST(){}
    bool find(int val) {
        if (this->val==INT_MIN) return false;
        BST* curr=this;
        while (curr) {
            if (val>curr->val) curr=curr->right;
            else if (val<curr->val) curr=curr->left;
            else if (val==curr->val) return true;
        }
        return false;
    }
    void insert(int val) {
        if (this->val==INT_MIN) {
            this->val=val;
            return;
        }
        if (this->find(val)==true) return;
        BST* curr=this;
        while (curr) {
            if (val>curr->val) {
                if (curr->right) curr=curr->right;
                else if (!curr->right) {
                    curr->right=new BST();
                    curr->right->val=val;
                    return;
                }
            }
            else if (val<curr->val) {
                if (curr->left) curr=curr->left;
                else if (!curr->left) {
                    curr->left=new BST();
                    curr->left->val=val;
                    return;
                }
            }
        }
    }
    int sum() {
        int sum=0;
        queue<BST*> q;
        q.push(this);
        while (!q.empty()) {
            BST* curr=q.front();
            q.pop();
            sum+=curr->val;
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        return sum;
    }
    void BFS() {
        if (this->val==INT_MIN) return;
        queue<BST*>q;
        q.push(this);
        while (!q.empty()) {
            BST* curr=q.front();
            q.pop();
            cout<<curr->val<<" ";
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
        cout<<endl;
    }
    //DFS with recursion
    void preorder_rec() {
        if (this->val==INT_MIN) return;
        cout<<this->val<<" ";
        if (this->left) this->left->preorder_rec();
        if (this->right) this->right->preorder_rec();
    }
    void inorder_rec() {
        if (this->val==INT_MIN) return;
        if (this->left) this->left->inorder_rec();
        cout<<this->val<<" ";
        if (this->right) this->right->inorder_rec();
    }
    void postorder_rec() {
        if (this->val==INT_MIN) return;
        if (this->left) this->left->postorder_rec();
        if (this->right) this->right->postorder_rec();
        cout<<this->val<<" ";
    }
    //DFS without recursion
    void preorder() {
        if (this->val==INT_MIN) return;
        stack<BST*>s;
        s.push(this);
        while (!s.empty()) {
            BST* curr=s.top();
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
        stack<BST*> s;
        BST* curr=this;
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
        stack<BST*> s;
        BST* curr = this;
        BST* lastVisited = nullptr;
        while (curr || !s.empty()) {
            if (curr) {
                s.push(curr);
                curr = curr->left;
            }
            else {
                BST* peekNode = s.top();
                if (peekNode->right!=nullptr && lastVisited!=peekNode->right) {
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
    BST t;
    t.insert(4);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(7);
    t.BFS();
    cout<<t.find(2)<<endl;
    cout<<t.sum()<<endl;
    t.preorder_rec();
    cout<<endl;
    t.preorder();
    t.inorder_rec();
    cout<<endl;
    t.inorder();
    t.postorder_rec();
    cout<<endl;
    t.postorder();
}