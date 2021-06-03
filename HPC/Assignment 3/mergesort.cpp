#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void merge(vector<int> &v,int l,int m,int r) {
    int i=l,j=m+1;
    vector<int> a;
    while(i<=m && j<=r) {
        if(v[i]>v[j]) {
            a.push_back(v[j]);
            j+=1;
        }
        else {
            a.push_back(v[i]);
            i+=1;
        }
    }
    while(i<=m) {
        a.push_back(v[i]);
        i+=1;
    }
    while(j<=r) {
        a.push_back(v[j]);
        j+=1;
    }
    for(int i=l;i<=r;i++)
        v[i]=a[i-l];
}

void mergeSort(vector<int> &v,int l,int r) {
    if(l<r) {
        int m=(l+r)/2;
        #pragma omp parallel sections 
        {
            #pragma omp section
            mergeSort(v,l,m);
            #pragma omp section
            mergeSort(v,m+1,r);
        }
        merge(v,l,m,r);
    }
}

void _mergeSort(vector<int> &v,int l,int r) {
    if(l<r) {
        int m=(l+r)/2;
        mergeSort(v,l,m);
        mergeSort(v,m+1,r);
        merge(v,l,m,r);
    }
}

int main() {
    cout<<"Merge Sort\n\n";
    int n=50;
    vector<int> v,vv;
    omp_set_num_threads(2);
    for(int i=0;i<n;i++)
        v.push_back(rand()%n);
    vv=v;

    double st=omp_get_wtime();
    mergeSort(v,0,n-1);
    double en=omp_get_wtime();

    // for(int i=0;i<n;i++)
    //     cout<<v[i]<<" ";
    // cout<<endl;

    

    double st1=omp_get_wtime();
    _mergeSort(vv,0,n-1);
    double en1=omp_get_wtime();

    cout<<"Serial Time : "<<en1-st1<<endl;
    cout<<"Parallel Time : "<<en-st<<endl;

    cout<<"Result :\n";
    for(int i=0;i<n;i++)
        cout<<v[i]<<" ";
    cout<<endl;

    return 0;
}