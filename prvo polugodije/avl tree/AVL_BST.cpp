#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class AVL_BST {
public:
    int x;
    int hgt;
    AVL_BST* l;
    AVL_BST* r;

    AVL_BST(int v) {
        x = v;
        hgt = 1;
        l = r = nullptr;
    }

    int getH(AVL_BST* t) {
        if (!t) return 0;
        return t->hgt;
    }

    void fix(AVL_BST* t) {
        int a = getH(t->l);
        int b = getH(t->r);
        t->hgt = max(a, b) + 1;
    }

    int bf(AVL_BST* t) {
        if (!t) return 0;
        return getH(t->l) - getH(t->r);
    }

    AVL_BST* rotR(AVL_BST* t) {
        AVL_BST* y = t->l;
        AVL_BST* tmp = y->r;

        y->r = t;
        t->l = tmp;

        fix(t);
        fix(y);

        return y;
    }

    AVL_BST* rotL(AVL_BST* t) {
        AVL_BST* y = t->r;
        AVL_BST* tmp = y->l;

        y->l = t;
        t->r = tmp;

        fix(t);
        fix(y);

        return y;
    }

    void insert(AVL_BST*& t, int v) {
        if (!t) {
            t = new AVL_BST(v);
            return;
        }

        if (v < t->x)
            insert(t->l, v);
        else if (v > t->x)
            insert(t->r, v);
        else
            return;

        fix(t);

        int b = bf(t);

        if (b > 1 && v < t->l->x)
            t = rotR(t);

        else if (b < -1 && v > t->r->x)
            t = rotL(t);

        else if (b > 1 && v > t->l->x) {
            t->l = rotL(t->l);
            t = rotR(t);
        }

        else if (b < -1 && v < t->r->x) {
            t->r = rotR(t->r);
            t = rotL(t);
        }
    }

    AVL_BST* mn(AVL_BST* t) {
        while (t->l)
            t = t->l;
        return t;
    }

    void remove(AVL_BST*& t, int v) {
        if (!t) return;

        if (v < t->x)
            remove(t->l, v);
        else if (v > t->x)
            remove(t->r, v);
        else {
            if (!t->l || !t->r) {
                AVL_BST* tmp = t->l ? t->l : t->r;
                delete t;
                t = tmp;
            }
            else {
                AVL_BST* tmp = mn(t->r);
                t->x = tmp->x;
                remove(t->r, tmp->x);
            }
        }

        if (!t) return;

        fix(t);

        int b = bf(t);

        if (b > 1 && bf(t->l) >= 0)
            t = rotR(t);

        else if (b > 1 && bf(t->l) < 0) {
            t->l = rotL(t->l);
            t = rotR(t);
        }

        else if (b < -1 && bf(t->r) <= 0)
            t = rotL(t);

        else if (b < -1 && bf(t->r) > 0) {
            t->r = rotR(t->r);
            t = rotL(t);
        }
    }

    void inorder_rec() {
        if (l) l->inorder_rec();
        cout << x << " ";
        if (r) r->inorder_rec();
    }
};

int main() {
    AVL_BST* root = nullptr;
    AVL_BST util(0);

    util.insert(root, 10);
    util.insert(root, 20);
    util.insert(root, 30);
    util.insert(root, 40);
    util.insert(root, 25);

    root->inorder_rec();
    cout << endl;

    util.remove(root, 30);

    root->inorder_rec();
}
