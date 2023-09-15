#include<bits/stdc++.h>
using namespace std;
#define duonghoan21 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int maxn = 1e6;
int n,a[maxn];

void outArray(){
    for(int i =  0 ; i < n; ++i){
        cout << a[i] << " ";
    }
    cout <<'\n';
}
void quickSort( int left, int right)
{ 	
	int	i, j, x;
	if (left >= right)	return;
  	int mid = left+right >> 1;
  	i = left; j = right;
  	 do{
     	while(a[i] < a[mid]) i++;
     	while(a[j] > a[mid]) j--;
     	if(i <= j) { 
			swap(a[i], a[j]);
       		i++ ; j--;
	 	}
	} while(i < j);
	if(left<j) quickSort(left, j);
	if(i<right) quickSort( i, right);
}


int main(){
    duonghoan21
    freopen("in.txt","r",stdin);freopen("out.txt","w",stdout);
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];
    quickSort(0,n-1);
    outArray();
    return 0;
}