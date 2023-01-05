#include <cstdio>

int main()
{
	int a[4], ans;
	bool clockwise;
	while(true){
		scanf("%d %d %d %d", a, a+1, a+2, a+3);
		if (a[0]==0 && a[1]==0 && a[2]==0 && a[3]==0) break;
		ans = 1080;
		clockwise=false;
		for(int n=1; n<4; n++, clockwise=!clockwise){
			if (clockwise){
				if (a[n]>=a[n-1]) ans+=(a[n]-a[n-1])*9;
				else ans+=(a[n]-a[n-1]+40)*9;
			}
			else{
				if (a[n]<=a[n-1]) ans+=(a[n-1]-a[n])*9;
				else ans+=(a[n-1]-a[n]+40)*9;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}