#include <bits/stdc++.h>
using namespace std;
#define duonghoan21 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int maxn = 1e6;
int n,a[maxn];

void outArray(){
    for(int i = 0; i < n; ++i){
        cout << a[i] << " ";
    }
    cout << "\n";
}

void bubbleSort(){
    for(int i = 0; i < n; ++i){
        for(int j = n-1; j > i ; j--){
            if (a[j] < a[j-1]) swap(a[j],a[j-1]);
        }
    }
}

int main(){
    duonghoan21
    freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
    cin >> n;
    for(int i = 0 ; i < n; ++i) cin >> a[i];
    bubbleSort();
    outArray(); // check Array is sorted
    return 0;
}