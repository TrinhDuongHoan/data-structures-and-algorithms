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
void selectionSort(){
    for(int i = 0 ; i < n-1; ++i){
        int min_id = i;
        for(int j = i+1; j < n; ++j){
            if (a[j] < a[min_id]) min_id = j;
        }
        if (min_id != i) swap(a[i],a[min_id]);
    }
}

int main(){
    duonghoan21
    freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
    cin >> n;
    for(int i = 0 ; i < n; ++i) cin >> a[i];
    selectionSort();
    outArray(); // check Array is sorted
    return 0;
}