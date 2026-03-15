#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>

//Mergesort, insertionsort i selectionsort i bonus quicksort nizata neka e 10^5 random broevi i da se vidi kolku vreme im treba


using namespace std;
using namespace std::chrono;


void inserts(int arr[],int n){
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
    
    while(j>=0 && arr[j]>key){
        arr[j+1]=arr[j];
        j--;
    }
    arr[j+1]=key;
}
}

void seles(int arr[], int n){
    for(int i=0;i<n-1;i++){
        int mini=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[mini]){
                mini=j;
            }
        }
        if(mini!=i){
            int t=arr[i];
            arr[i]=arr[mini];
            arr[mini]=t;
        }
    }
}

void merge(int arr[],int l, int m, int r){
    int n1=m-l+1;
    int n2=r-m;

    int *L=new int[n1];
    int *R=new int[n2];

    for (int i=0;i<n1;i++)
        L[i]=arr[l+i];
    for (int j=0;j<n2;j++)
        R[j]=arr[m+1+j];

       int i=0,j=0,k=l;
    while (i<n1 && j<n2) {
        if (L[i]<=R[j]) {
            arr[k++]=L[i++];
        } else {
            arr[k++]=R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
} 

void mergeSort(int arr[],int l,int r) {
    if (l < r) {
        int m=l+(r-l)/2;
        mergeSort(arr,l,m); 
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);   
    }
}
       
int main()
{
    auto start=high_resolution_clock::now();
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,100000);
    int n=100000;
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=dist(gen);
    }
    mergeSort(arr,0,n-1);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }

     auto end=high_resolution_clock::now();
     auto duration=duration_cast<milliseconds>(end-start);
    cout <<"Vreme: "<<duration.count()<<" ms\n";
}
