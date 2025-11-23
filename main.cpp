#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;
    BST() {
        root = nullptr;
    }

    Node* insert(Node* node, int v) {
        if(node == nullptr) return new Node(v);
        if(v < node->val) node->left = insert(node->left, v);
        else node->right = insert(node->right, v);
        return node;
    }

    void insert(int v) {
        root = insert(root, v);
    }

    bool find(Node* node, int v) {
        if(node == nullptr) return false;
        if(node->val == v) return true;
        if(v < node->val) return find(node->left, v);
        return find(node->right, v);
    }

    void preorder(Node* node) {
        if(!node) return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if(!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void postorder(Node* node) {
        if(!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }

    void preorderNR() {
        if(!root) return;
        stack<Node*> st;
        st.push(root);
        while(!st.empty()) {
            Node* cur = st.top(); st.pop();
            cout << cur->val << " ";

            if(cur->right) st.push(cur->right);
            if(cur->left) st.push(cur->left);
        }
    }

    void inorderNR() {
        stack<Node*> st;
        Node* cur = root;
        while(cur || !st.empty()) {
            while(cur) {
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top(); st.pop();
            cout << cur->val << " ";
            cur = cur->right;
        }
    }

    void postorderNR() {
        if(!root) return;
        stack<Node*> s1, s2;
        s1.push(root);
        while(!s1.empty()) {
            Node* cur = s1.top(); s1.pop();
            s2.push(cur);

            if(cur->left) s1.push(cur->left);
            if(cur->right) s1.push(cur->right);
        }
        while(!s2.empty()) {
            cout << s2.top()->val << " ";
            s2.pop();
        }
    }

    void bfs() {
        if(!root) return;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* cur = q.front(); q.pop();
            cout << cur->val << " ";

            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }
    }

    // сумата
    int sum(Node* node) {
        if(!node) return 0;
        return node->val + sum(node->left) + sum(node->right);
    }
};

int main() {
    BST t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(1);
    t.insert(4);

    cout << "Inorder: ";
    t.inorder(t.root);
    cout << endl;

    cout << "Preorder nr: ";
    t.preorderNR();
    cout << endl;

    cout << "bfs: ";
    t.bfs();
    cout << endl;

    cout << "Find 4: " << (t.find(t.root,4)?"da":"ne") << endl;
    cout << "sum: " << t.sum(t.root) << endl;

    return 0;
}