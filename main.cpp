#include <iostream>
#include <vector>
#import<math.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
vector <long long> interclasare(vector <long long> &a, vector <long long>& b)
{
    static vector<long long>c;
    c.resize(0);
    int i=0;int j=0;
    while(i<a.size() && j<b.size()){
        if(a[i]<b[j]) {
            c.push_back(a[i]);
            i++;
         }
        else if(a[i]>b[j]) {
            c.push_back(b[j]);
            j++;
        }
        else {
            c.push_back(a[i]);
            c.push_back(b[j]);
            i++;
            j++;
        }
    }
    while(i<a.size()){
        c.push_back(a[i]);
        i++;
    }
    while(j<b.size()){
        c.push_back(b[j]);
        j++;
    }
    return c;
}

void merge_sort(vector<long long>&v) {
    if (v.size() > 1) {
        int m = v.size() >> 1;
        vector<long long> a(v.begin(), v.begin() + m);
        vector<long long> b(v.begin() + m, v.end());
        merge_sort(a);
        merge_sort(b);
        v = interclasare(a, b);
    }
}
vector<long long> CountingSort(vector<long long> v, long long n){
    clock_t tStart = clock();

    vector<long long> fr(n,0);
    for(auto it:v) fr[it]++;
    v.clear();
    for (long long i=0;i<n;i++) while(fr[i]!=0) {v.push_back(i);fr[i]--;}
    cout.precision(5);
    cout << fixed <<  float(clock() - tStart)/CLOCKS_PER_SEC  <<"sec  //  ";
    return v;
}


void gap_generator(long n, vector<long long>& v){
    for(int i=1;i<=1000000;i++){
        if((pow(3,i)-1)/2>n) break;
        v.push_back((pow(3,i)-1)/2);

    }
}

vector<long long> shell_sort(vector<long long> v, int n) {
    vector<long long>vv;
    gap_generator(n,vv);
    clock_t tStart = clock();
    for (long long ind = vv.size(); ind >= 0; ind--) {
        long long gap=vv[ind];
        for (int i = gap; i < n; i += 1) {
            int crt = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > crt; j -= gap) {
                v[j]=v[j - gap];
            }
            v[j] = crt;
        }
    }
    cout.precision(5);
    cout << fixed <<  float(clock() - tStart)/CLOCKS_PER_SEC  << "sec  //  ";
    return v;
}

void gap_generator2(long n, vector<long long>& v){
    for(int i=1;i<=1000000;i++){
        if((pow(2,i)-1)>n) break;
        v.push_back((pow(2,i)-1));

    }
}

vector<long long> shell_sort2(vector<long long> v, int n) {
    vector<long long>vv;
    gap_generator2(n,vv);
    clock_t tStart = clock();
    for (long long ind = vv.size(); ind >= 0; ind--) {
        long long gap=vv[ind];
        for (int i = gap; i < n; i += 1) {
            int crt = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > crt; j -= gap) {
                v[j]=v[j - gap];
            }
            v[j] = crt;
        }
    }
    cout.precision(5);
    cout << fixed <<  float(clock() - tStart)/CLOCKS_PER_SEC  <<"sec  //  ";
    return v;
}


long long maxim(vector<long long> v, long long n) {
    long long max = v[0];
    for (long long i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;}

vector<long long> countingSort(vector<long long> v, long long n, long long exp) {
    vector<long long> output(n,-1);
    vector<long long> count(10,0);

    for (int i = 0; i < n; i++)
        count[(v[i]/exp)%10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }
    v.empty();
    for (int i = 0; i < n; i++)
        v[i] = output[i];
    return v;
}
vector <long long> radixsort(vector<long long> v, long long n) {
    clock_t tStart = clock();

    long long max = maxim(v, n);
    for (long long exp = 1; max / exp > 0; exp *= 10)
        v=countingSort(v, n, exp);
    cout.precision(5);
    cout << fixed <<  float(clock() - tStart)/CLOCKS_PER_SEC  <<"sec  //  ";
    return v;

}



vector<long long> countingSort2(vector<long long> v, long long n, long long exp) {
    vector<long long> output(n,-1);
    vector<long long> count(10,0);
    long long p = pow(2,exp);
    for (int i = 0; i < n; i++)
        count[(v[i]>>exp)&(p-1)]++;   ///x % 2^n      x & (2^n - 1)

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(v[i]>>exp) &(p-1)] - 1] = v[i];
        count[(v[i] >> exp) &(p-1)]--;
    }
    v.empty();
    for (int i = 0; i < n; i++)
        v[i] = output[i];
    return v;
}
vector <long long> radixsort2(vector<long long> v, long long n) {
    clock_t tStart = clock();

    long long max = maxim(v, n);
    for (long long exp = 1; max>>exp > 0; exp+=16)
        v=countingSort2(v, n, exp);
    cout.precision(5);
    cout << fixed <<  float(clock() - tStart)/CLOCKS_PER_SEC  << endl;
    return v;

}


int partition (vector<long long> &v, long long low, long long high)
{
    long long pivot = low + rand()%(high-low); // pivot
    swap(v[pivot],v[high]);
    pivot = v[high];
    long long i = (low - 1);

    for (long long j = low; j <= high - 1; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return (i + 1);
}

void quickSort(vector<long long>&v , long long low, long long high)
{
    if (low < high)
    {
        long long pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

bool sortat_bine (vector<long long> v, vector<long long> a) {
    for (int i = 0; i < v.size(); ++i)
        if (v[i] != a[i]) return false;
    return true;
}

int main(void) {
    srand(time(0));
    int i=0;
    vector<long long> v1, v2, v3, v4, v5, v6,v7,v8;

    for(long long n=1000;n<=100000000;n*=10){
     cout<<"Test"<<" "<<++i<<", N = "<<n<<": "<<endl;

    for (long long i = 1; i <= n; i++) {
        v1.push_back(rand() % 1000000);
        v2.push_back(v1[v1.size() - 1]);
        v3.push_back(v1[v1.size() - 1]);
        v4.push_back(v1[v1.size() - 1]);
        v5.push_back(v1[v1.size() - 1]);
        v6.push_back(v1[v1.size() - 1]);
        v7.push_back(v1[v1.size() - 1]);
        v8.push_back(v1[v1.size() - 1]);
    }

//1) Stl Sort
     cout<<"Stl Sort: ";
        clock_t tStart = clock();
        sort(v6.begin(),v6.end());
        cout.precision(5);
        cout << fixed << float(clock() - tStart) / CLOCKS_PER_SEC << endl;

//2) Shell Sort (Gap (3^k-1)/2 )
    cout << "Shell sort, gap (3^k-1)/2: ";
    v1 = shell_sort(v1, n);
    if(sortat_bine(v1,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;
//3) Shell Sort (Gap (2^k-1) )
        cout << "Shell sort, gap (2^k-1): ";
        v7 = shell_sort(v7, n);
        if(sortat_bine(v7,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;


//4) Merge Sort
    cout << "MergeSort: ";
     tStart = clock();
    merge_sort(v2);
    cout.precision(5);
    cout << fixed << float(clock() - tStart) / CLOCKS_PER_SEC <<"sec  //  ";
    if(sortat_bine(v2,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;

//5) Radix Sort baza 10
    cout << "RadixSort baza 10: ";
    v3 = radixsort(v3, n);
    if(sortat_bine(v3,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;

//6) Radix Sort baza 2^16
        cout << "RadixSort baza 2^16: ";
        v8 = radixsort(v8, n);
        if(sortat_bine(v8,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;

//7) Counting Sort
    cout << "CountingSort: ";
    v4 = CountingSort(v4, n);
    if(sortat_bine(v4,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;

//8) Quick Sort
    cout << "QuickSort: ";
    tStart = clock();
    quickSort(v5, 0, n - 1);
    cout.precision(5);
    cout << fixed << float(clock() - tStart) / CLOCKS_PER_SEC <<"sec  //  ";
    if(sortat_bine(v5,v6)) cout<<"Sortat cu succes"<<endl; else cout<<"Nu a fost sortat"<<endl;

    cout << "----------------------------------------------------------------" << endl;
    v1.clear();v2.clear();v3.clear();v4.clear();v5.clear();v6.clear();v7.clear();v8.clear();
}
}