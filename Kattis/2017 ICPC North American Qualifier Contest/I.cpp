#include <bits/stdc++.h>
using namespace std;
#define INF 1e9

int arr[1009];
int val[1009];
int n;

bool solve(int idx){
	int k = 0,wmin = INF;
	int idx2;
	
	for (int i=(idx+1)%n;i!=idx;i=(i+1)%n){
		val[k] = arr[i];
		if (arr[i]<wmin){wmin = arr[i], idx2 = k;}
		k++;
	}
	int prev = val[idx2];
	for (int i=(idx2+1)%k;i!=idx2;i=(i+1)%k){
		if (val[i]!=prev+1)return false;
		prev++;
	}
	
	return true;
}

int main(){
	int t,j;
	cin>>t;
	while (t-->0){
		cin>>n;
		for (int i=0;i<n;i++)cin>>arr[i];
		for (j=1;j<n-1;j++)if (solve(j))break;
		cout<<j+1<<endl;
	}
}