#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class AVL_BST {
public:
    int val;
    int height;
    AVL_BST* left;
    AVL_BST* right;
    AVL_BST(int v) {
        val = v;
        height = 1;
        left = right = nullptr;
    }
    int h(AVL_BST* t) {
        if (t == nullptr) return 0;
        return t->height;
    }
    void update(AVL_BST* t) {
        int hl = h(t->left);
        int hr = h(t->right);
        t->height = max(hl, hr) + 1;
    }
    int balance(AVL_BST* t) {
        if (t == nullptr) return 0;
        return h(t->left) - h(t->right);
    }
    AVL_BST* rotateRight(AVL_BST* t) {
        AVL_BST* x = t->left;
        AVL_BST* T2 = x->right;
        x->right = t;
        t->left = T2;
        update(t);
        update(x);
        return x;
    }
    AVL_BST* rotateLeft(AVL_BST* t) {
        AVL_BST* x = t->right;
        AVL_BST* T2 = x->left;
        x->left = t;
        t->right = T2;
        update(t);
        update(x);
        return x;
    }
    void insert(AVL_BST*& t, int v) {
        if (t == nullptr) {
            t = new AVL_BST(v);
            return;
        }
        if (v < t->val)
            insert(t->left, v);
        else if (v > t->val)
            insert(t->right, v);
        else
            return;
        update(t);
        int b = balance(t);

        if (b > 1 && v < t->left->val)
            t = rotateRight(t);
        else if (b < -1 && v > t->right->val)
            t = rotateLeft(t);
        else if (b > 1 && v > t->left->val) {
            t->left = rotateLeft(t->left);
            t = rotateRight(t);
        }
        else if (b < -1 && v < t->right->val) {
            t->right = rotateRight(t->right);
            t = rotateLeft(t);
        }
    }
    AVL_BST* minNode(AVL_BST* t) {
        while (t->left)
            t = t->left;
        return t;
    }
    void remove(AVL_BST*& t, int v) {
        if (t == nullptr) return;
        if (v < t->val)
            remove(t->left, v);
        else if (v > t->val)
            remove(t->right, v);
        else {
            if (!t->left || !t->right) {
                AVL_BST* temp = t->left ? t->left : t->right;
                delete t;
                t = temp;
            }
            else {
                AVL_BST* temp = minNode(t->right);
                t->val = temp->val;
                remove(t->right, temp->val);
            }
        }
        if (t == nullptr) return;
        update(t);
        int b = balance(t);
        if (b > 1 && balance(t->left) >= 0)
            t = rotateRight(t);
        else if (b > 1 && balance(t->left) < 0) {
            t->left = rotateLeft(t->left);
            t = rotateRight(t);
        }
        else if (b < -1 && balance(t->right) <= 0)
            t = rotateLeft(t);
        else if (b < -1 && balance(t->right) > 0) {
            t->right = rotateRight(t->right);
            t = rotateLeft(t);
        }
    }
    void inorder_rec() {
        if (left) left->inorder_rec();
        cout << val << " ";
        if (right) right->inorder_rec();
    }
};

int main() {
    AVL_BST* root = nullptr;
    AVL_BST helper(0);
    helper.insert(root, 10);
    helper.insert(root, 20);
    helper.insert(root, 30);
    helper.insert(root, 40);
    helper.insert(root, 25);
    root->inorder_rec();
    cout << endl;
    helper.remove(root, 30);
    root->inorder_rec();
}
