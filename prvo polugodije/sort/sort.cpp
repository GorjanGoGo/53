#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& a){
    for(int i=1;i<a.size();i++){
        int key=a[i];
        int j=i-1;
        while(j>=0 && a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}

void merge(vector<int>& a,int l,int m,int r){
    vector<int> L(a.begin()+l,a.begin()+m+1);
    vector<int> R(a.begin()+m+1,a.begin()+r+1);
    int i=0,j=0,k=l;
    while(i<L.size() && j<R.size()){
        if(L[i]<=R[j]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    while(i<L.size()) a[k++]=L[i++];
    while(j<R.size()) a[k++]=R[j++];
}

void mergeSort(vector<int>& a,int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(a,l,m);
        mergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}

int partition(vector<int>& a,int l,int r){
    int pivot=a[r],i=l-1;
    for(int j=l;j<r;j++){
        if(a[j]<pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[i+1],a[r]);
    return i+1;
}

void quickSort(vector<int>& a,int l,int r){
    if(l<r){
        int pi=partition(a,l,r);
        quickSort(a,l,pi-1);
        quickSort(a,pi+1,r);
    }
}

int main(){
    srand(time(0));
    int n=100000;
    vector<int> a(n),b(n),c(n);
    for(int i=0;i<n;i++){
        int x=rand()%100000+1;
        a[i]=b[i]=c[i]=x;
    }

    insertionSort(a);
    mergeSort(b,0,n-1);
    quickSort(c,0,n-1);
}
