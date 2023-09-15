#include<bits/stdc++.h>
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
void insertionSort(){
    for(int i = 1; i < n; ++i){
        int pos= i-1, key = a[i];
        while(pos >= 0 && a[pos] > key  ){
            a[pos+1] = a[pos];
            pos--;
        }
        a[pos+1] = key;
    }
}

int main(){
    duonghoan21
    freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
    cin >> n;
    for(int i = 0 ; i < n; ++i) cin >> a[i];
    insertionSort();
    outArray(); // check Array is sorted
    return 0;
}