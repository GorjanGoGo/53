#include <iostream>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

class BST {
    int x;
    BST* l;
    BST* r;

public:
    BST(){
        x = INT_MIN;
        l = nullptr;
        r = nullptr;
    }

    ~BST(){}

    bool find(int v){
        if(x == INT_MIN) return false;

        BST* cur = this;
        while(cur){
            if(v > cur->x) cur = cur->r;
            else if(v < cur->x) cur = cur->l;
            else return true;
        }

        return false;
    }

    void insert(int v){
        if(x == INT_MIN){
            x = v;
            return;
        }
        if(find(v)) return;

        BST* cur = this;

        while(true){
            if(v > cur->x){
                if(cur->r) cur = cur->r;
                else{
                    cur->r = new BST();
                    cur->r->x = v;
                    return;
                }
            }
            else{
                if(cur->l) cur = cur->l;
                else{
                    cur->l = new BST();
                    cur->l->x = v;
                    return;
                }
            }
        }
    }

    int sum(){
        int s = 0;
        queue<BST*> q;
        q.push(this);

        while(!q.empty()){
            BST* cur = q.front();
            q.pop();

            s += cur->x;

            if(cur->l) q.push(cur->l);
            if(cur->r) q.push(cur->r);
        }

        return s;
    }

    void BFS(){
        if(x == INT_MIN) return;

        queue<BST*> q;
        q.push(this);

        while(!q.empty()){
            BST* cur = q.front();
            q.pop();

            cout << cur->x << " ";

            if(cur->l) q.push(cur->l);
            if(cur->r) q.push(cur->r);
        }

        cout << endl;
    }

    void preorder_rec(){
        if(x == INT_MIN) return;

        cout << x << " ";
        if(l) l->preorder_rec();
        if(r) r->preorder_rec();
    }

    void inorder_rec(){
        if(x == INT_MIN) return;

        if(l) l->inorder_rec();
        cout << x << " ";
        if(r) r->inorder_rec();
    }

    void postorder_rec(){
        if(x == INT_MIN) return;

        if(l) l->postorder_rec();
        if(r) r->postorder_rec();
        cout << x << " ";
    }

    void preorder(){
        if(x == INT_MIN) return;

        stack<BST*> st;
        st.push(this);

        while(!st.empty()){
            BST* cur = st.top();
            st.pop();

            cout << cur->x << " ";

            if(cur->r) st.push(cur->r);
            if(cur->l) st.push(cur->l);
        }

        cout << endl;
    }

    void inorder(){
        if(x == INT_MIN) return;

        stack<BST*> st;
        BST* cur = this;

        while(cur || !st.empty()){

            while(cur){
                st.push(cur);
                cur = cur->l;
            }

            cur = st.top();
            st.pop();

            cout << cur->x << " ";

            cur = cur->r;
        }

        cout << endl;
    }

    void postorder(){
        if(x == INT_MIN) return;

        stack<BST*> st;
        BST* cur = this;
        BST* last = nullptr;

        while(cur || !st.empty()){

            if(cur){
                st.push(cur);
                cur = cur->l;
            }
            else{
                BST* t = st.top();
                if(t->r && last != t->r){
                    cur = t->r;
                }
                else{
                    cout << t->x << " ";
                    last = t;
                    st.pop();
                }
            }
        }

        cout << endl;
    }
};

int main(){
    BST t;

    t.insert(4);
    t.insert(2);
    t.insert(6);
    t.insert(1);
    t.insert(3);
    t.insert(5);
    t.insert(7);

    t.BFS();

    cout << t.find(2) << endl;
    cout << t.sum() << endl;

    t.preorder_rec();
    cout << endl;

    t.preorder();

    t.inorder_rec();
    cout << endl;

    t.inorder();

    t.postorder_rec();
    cout << endl;

    t.postorder();
}
