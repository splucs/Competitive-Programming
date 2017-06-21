#include <cstdio>

int main(){
	int n, maxi=-1, maxh=-1, h;
	scanf("%d", &n);
	bool tie = false;
	for(int i=1; i<=n; i++){
		scanf("%d", &h);
		if (h == maxh) tie = true;
		if (h > maxh){
			maxi = i;
			maxh = h;
			tie = false;
		}
	}
	if (tie) maxi = -1;
	printf("%d\n", maxi);
	return 0;
}