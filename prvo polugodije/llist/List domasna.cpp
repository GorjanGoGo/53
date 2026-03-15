#include <iostream>
#include <limits>
using namespace std;

struct Node{
    int val;
    Node* next;
};

struct linkedList{
    Node* head;
    linkedList(){head=nullptr;}
};

void insertNode(linkedList& l,int value){
    Node* newNode=new Node{value,nullptr};
    if(!l.head){l.head=newNode;return;}
    Node* p=l.head;
    while(p->next)p=p->next;
    p->next=newNode;
}

void insertNodeSorted(linkedList& l,int value){
    Node* newNode=new Node{value,nullptr};
    if(!l.head||value<l.head->val){
        newNode->next=l.head;
        l.head=newNode;
        return;
    }
    Node* p=l.head;
    while(p->next&&p->next->val<value)p=p->next;
    newNode->next=p->next;
    p->next=newNode;
}

void removeNode(linkedList& l,int value,bool remove_all=false){
    while(l.head&&l.head->val==value){
        Node* tmp=l.head;
        l.head=l.head->next;
        delete tmp;
        if(!remove_all)return;
    }
    Node* p=l.head;
    while(p&&p->next){
        if(p->next->val==value){
            Node* tmp=p->next;
            p->next=tmp->next;
            delete tmp;
            if(!remove_all)return;
        }else p=p->next;
    }
}

void outputList(linkedList& l){
    Node* p=l.head;
    while(p){
        cout<<p->val<<" ";
        p=p->next;
    }
    cout<<"\n";
}

void mergeSortedLists(linkedList& A,linkedList& B,linkedList& result){
    Node* a=A.head;
    Node* b=B.head;
    Node* tail=nullptr;
    result.head=nullptr;
    while(a||b){
        int val;
        if(!b||(a&&a->val<b->val)){
            val=a->val;
            a=a->next;
        }else if(!a||(b&&b->val<a->val)){
            val=b->val;
            b=b->next;
        }else{
            val=a->val;
            a=a->next;
            b=b->next;
        }
        if(result.head==nullptr||tail->val!=val){
            Node* newNode=new Node{val,nullptr};
            if(result.head==nullptr)result.head=newNode;
            else tail->next=newNode;
            tail=newNode;
        }
    }
}

void bubbleSort(linkedList& l){
    if(!l.head)return;
    bool swapped;
    do{
        swapped=false;
        Node* p=l.head;
        while(p->next){
            if(p->val>p->next->val){
                swap(p->val,p->next->val);
                swapped=true;
            }
            p=p->next;
        }
    }while(swapped);
}

void insertionSort(linkedList& l){
    Node* sorted=nullptr;
    Node* cur=l.head;
    while(cur){
        Node* next=cur->next;
        if(!sorted||sorted->val>=cur->val){
            cur->next=sorted;
            sorted=cur;
        }else{
            Node* p=sorted;
            while(p->next&&p->next->val<cur->val)p=p->next;
            cur->next=p->next;
            p->next=cur;
        }
        cur=next;
    }
    l.head=sorted;
}

struct DNode{
    int val;
    DNode* next;
    DNode* prev;
};

struct doublyList{
    DNode* head;
    DNode* tail;
    doublyList(){head=tail=nullptr;}
};

void addNode(doublyList& l,int value,int position=-1){
    DNode* newNode=new DNode{value,nullptr,nullptr};
    if(!l.head){l.head=l.tail=newNode;return;}
    if(position<=0){
        newNode->prev=l.tail;
        l.tail->next=newNode;
        l.tail=newNode;
        return;
    }
    DNode* p=l.head;
    int i=0;
    while(p->next&&i<position-1){p=p->next;i++;}
    newNode->next=p->next;
    newNode->prev=p;
    if(p->next)p->next->prev=newNode;
    else l.tail=newNode;
    p->next=newNode;
}

void removeNode(doublyList& l,int value){
    DNode* p=l.head;
    while(p){
        if(p->val==value){
            if(p->prev)p->prev->next=p->next;
            else l.head=p->next;
            if(p->next)p->next->prev=p->prev;
            else l.tail=p->prev;
            delete p;
            return;
        }
        p=p->next;
    }
}

DNode* search(doublyList& l,int value){
    DNode* p=l.head;
    while(p){
        if(p->val==value)return p;
        p=p->next;
    }
    return nullptr;
}

void outputList(const doublyList& l){
    cout<<"Од почеток "<<endl;
    DNode* p=l.head;
    while(p){cout<<p->val<<" ";p=p->next;}
    cout<<"Од крај "<<endl;
    p=l.tail;
    while(p){cout<<p->val<<" ";p=p->prev;}
    cout<<"\n";
}

int main(){
    cout<<"1: Сортирано внесување"<<endl;
    linkedList L;
    int x;
    cout<<"Внесувај броеви 0 за стоп"<<endl;
    while(cin>>x&&x!=0)insertNodeSorted(L,x);
    cout<<"Сортирана листа: "<<endl;
    outputList(L);

    cout<<"2: Спојување две листи без дупликати"<<endl;
    linkedList L1,L2,M;
    insertNodeSorted(L1,1);
    insertNodeSorted(L1,3);
    insertNodeSorted(L1,5);
    insertNodeSorted(L2,2);
    insertNodeSorted(L2,3);
    insertNodeSorted(L2,4);
    cout<<"Листа 1: ";outputList(L1);
    cout<<"Листа 2: ";outputList(L2);
    mergeSortedLists(L1,L2,M);
    cout<<"Споена листа: ";outputList(M);

    cout<<"3: Bubble и Insertion sort "<<endl;
    linkedList L3;
    insertNode(L3,5);
    insertNode(L3,2);
    insertNode(L3,8);
    insertNode(L3,1);
    cout<<"Почетна листа: "<<endl;outputList(L3);
    bubbleSort(L3);
    cout<<"По Bubble sort: "<<endl;outputList(L3);
    insertNode(L3,4);
    insertNode(L3,7);
    insertionSort(L3);
    cout<<"По Insertion sort: "<<endl;outputList(L3);

    cout<<"4: Двојно поврзана листа "<<endl;
    doublyList D;
    addNode(D,10);
    addNode(D,20);
    addNode(D,30);
    addNode(D,15,1);
    cout<<"По додавање:"<<endl;outputList(D);
    removeNode(D,20);
    cout<<"По бришење (20):"<<endl;outputList(D);
    DNode* found=search(D,15);
    if(found)cout<<"Пронајден елемент: "<<found->val<<endl;
    else cout<<"Елементот не е пронајден."<<endl;

    cout<<"Програмата заврши успешно "<<endl;
    return 0;
}

