#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int a,b,c,d,x,i;
	vector<int> inuse;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	for (i=2;i<=sqrt(c);i++){
		if (c%i==0){
			inuse.push_back(i),inuse.push_back(c/i);
		}
	}sort(inuse.begin(),inuse.end());
	for (i=0;i<(int)inuse.size();i++){
		x = inuse[i];
		if (x%a==0&&x%b!=0&&d%x!=0){
			printf("%d\n",x);
			break;
		}
	}if (i==(int)inuse.size())printf("-1\n");
	return 0;
}
