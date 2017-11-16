#include <bits/stdc++.h>
using namespace std;

int n;
int z[200000],s[200000];

void zfunction () {
	fill(z, z+n, 0);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
}

int main(){
    cin>>n;
    int cnt=1,a;
    for (int i=0;i<n;i++){
        cin>>a;
        if (a==0)s[i]=cnt++;
        else s[i] = s[a-1];
    }
    zfunction();
    for (int i=0;i<n;i++)cout<<z[i]<<" ";
    cout<<endl;
}