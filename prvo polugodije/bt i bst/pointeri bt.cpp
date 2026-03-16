#include <bits/stdc++.h>
using namespace std;

class Btree {
    int x;
    Btree* l;
    Btree* r;

public:
    Btree(){
        x = INT_MIN;
        l = nullptr;
        r = nullptr;
    }

    ~Btree(){}

    void insert(int v){
        if(x == INT_MIN){
            x = v;
            return;
        }

        queue<Btree*> q;
        q.push(this);

        while(true){
            Btree* cur = q.front();
            q.pop();

            if(!cur->l){
                cur->l = new Btree();
                cur->l->x = v;
                return;
            }
            else q.push(cur->l);

            if(!cur->r){
                cur->r = new Btree();
                cur->r->x = v;
                return;
            }
            else q.push(cur->r);
        }
    }

    bool find(int v){
        if(x == INT_MIN) return false;

        queue<Btree*> q;
        q.push(this);

        while(!q.empty()){
            Btree* cur = q.front();
            q.pop();

            if(cur->x == v) return true;

            if(cur->l) q.push(cur->l);
            if(cur->r) q.push(cur->r);
        }

        return false;
    }

    int sum(){
        int s = 0;
        queue<Btree*> q;
        q.push(this);

        while(!q.empty()){
            Btree* cur = q.front();
            q.pop();

            s += cur->x;

            if(cur->l) q.push(cur->l);
            if(cur->r) q.push(cur->r);
        }

        return s;
    }

    void BFS(){
        if(x == INT_MIN) return;

        queue<Btree*> q;
        q.push(this);

        while(!q.empty()){
            Btree* cur = q.front();
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

        stack<Btree*> st;
        st.push(this);

        while(!st.empty()){
            Btree* cur = st.top();
            st.pop();

            cout << cur->x << " ";

            if(cur->r) st.push(cur->r);
            if(cur->l) st.push(cur->l);
        }

        cout << endl;
    }

    void inorder(){
        if(x == INT_MIN) return;

        stack<Btree*> st;
        Btree* cur = this;

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

        stack<Btree*> st;
        Btree* cur = this;
        Btree* last = nullptr;

        while(cur || !st.empty()){

            if(cur){
                st.push(cur);
                cur = cur->l;
            }
            else{
                Btree* t = st.top();

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
    Btree t;

    for(int i = 1; i < 32; i++){
        t.insert(i);
    }

    cout << t.find(3) << endl;
    cout << t.sum() << endl;

    t.BFS();

    t.preorder_rec();
    cout << endl;

    t.preorder();

    t.inorder_rec();
    cout << endl;

    t.inorder();

    t.postorder_rec();
    cout << endl;

    t.postorder();

    return 0;
}
