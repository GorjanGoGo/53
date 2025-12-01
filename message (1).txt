#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;
    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

int h(Node* n) {
    return n ? n->height : 0;
}
int balance(Node* n) {
    return n ? h(n->left) - h(n->right) : 0;
}

void update(Node* n) {
    if(n) n->height = 1 + max(h(n->left), h(n->right));
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y); update(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x); update(y);
    return y;
}

Node* insertAVL(Node* root, int key) {
    if(!root) return new Node(key);
    if(key < root->key) root->left = insertAVL(root->left, key);
    else if(key > root->key) root->right = insertAVL(root->right, key);
    else return root;
    update(root);
    int bf = balance(root);
    if(bf > 1 && key < root->left->key) return rotateRight(root);
    if(bf < -1 && key > root->right->key) return rotateLeft(root);
    if(bf > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if(bf < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

bool findAVL(Node* root, int key) {
    if(!root) return false;
    if(root->key == key) return true;
    if(key < root->key) return findAVL(root->left, key);
    return findAVL(root->right, key);
}

void inorder(Node* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}


struct Entry {
    string key;
    Entry(string k) : key(k) {}
};

class CBHT {
public:
    int m;
    vector<vector<Entry>> table;
    int type;

    CBHT(int buckets, int t) {
        m = buckets;
        type = t;
        table.resize(m);
    }

    int hash1(const string &s) {
        return s.size() % m;
    }
    int hash2(const string &s) {
        int sum = 0;
        for(char c : s) sum += (tolower(c) - 'a' + 1);
        return sum % m;
    }
    int hash3(const string &s) {
        if(s.size() == 0) return 0;
        return (tolower(s[0]) - 'a' + 1) % m;
    }
    int hash4(const string &s) {
        int a = (s.size() > 0 ? tolower(s[0]) - 'a' + 1 : 0);
        int b = (s.size() > 1 ? tolower(s[1]) - 'a' + 1 : 0);
        return (a * 27 + b) % m;
    }

    int hashF(const string &s) {
        if(type==1) return hash1(s);
        if(type==2) return hash2(s);
        if(type==3) return hash3(s);
        return hash4(s);
    }

    void insertWord(const string &w) {
        int h = hashF(w);
        for(auto &e : table[h])
            if(e.key == w) return;
        table[h].push_back(Entry(w));
    }

    bool contains(const string &w) {
        int h = hashF(w);
        for(auto &e : table[h])
            if(e.key == w) return true;
        return false;
    }
};

int main() {
    Node* root = nullptr;
    root = insertAVL(root, 10);
    root = insertAVL(root, 20);
    root = insertAVL(root, 5);
    root = insertAVL(root, 4);
    root = insertAVL(root, 15);

    cout << "AVL inorder: ";
    inorder(root);
    cout<<endl;
    cout << "Find 15: " << findAVL(root, 15) <<endl;
    CBHT h1(50, 1); // hash by length
    h1.insertWord("hello");
    h1.insertWord("cat");
    h1.insertWord("the");

    cout << "Contains 'cat'? " << h1.contains("cat") <<endl;
    cout << "Contains 'dog'? " << h1.contains("dog") <<endl;

    return 0;
}
