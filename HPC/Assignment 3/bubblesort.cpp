#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}

int main()
{
    cout << "Bubble Sort\n\n";
    int n = 50;
    vector<int> v, vv;
    omp_set_num_threads(2);
    for (int i = 0; i < n; i++)
        v.push_back(rand() % n);
    vv = v;

    double st = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        int k = i % 2;
#pragma omp parallel for
        for (int j = k; j < n - 1; j += 2)
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
    }
    double en = omp_get_wtime();

    // for(int i=0;i<n;i++)
    //     cout<<v[i]<<" ";
    // cout<<endl;

    double st1 = omp_get_wtime();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (vv[j] > vv[j + 1])
                swap(vv[j], vv[j + 1]);
    double en1 = omp_get_wtime();

    cout << "Parallel Time : " << en1 - st1 << endl;
    cout << "Serial Time : " << en - st << endl;

    cout << "Result :\n";
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;

    return 0;
}