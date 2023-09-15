#include<bits/stdc++.h>
using namespace std;
#define duonghoan21 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int maxn = 1e6;
int n,a[maxn];

void binarySearch(int find){
    int left = 0, right = n-1;
    while(left<=right){
        int mid = (left+right)/2;
        if (a[mid] == find){
            cout << "Found in position : "<<mid<<endl;
            return;
        }
        else if (a[mid] < find) right = mid-1;
        else left = mid+1;
    }
    cout <<"Not found !!\n";
    return;
}


int main(){
    duonghoan21
    freopen("in.txt", "r", stdin);freopen("out.txt", "w", stdout);
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];
    sort(a,a+n);
    int x ; cin >> x; // x is the number to search for
    binarySearch(x);
    return 0;
}