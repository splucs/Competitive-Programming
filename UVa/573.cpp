#include <cstdio>

int main()
{
	int H, U, D, F;
	double currentHeight, fatigueFactor, fat;
	while(true){
		scanf("%d %d %d %d", &H, &U, &D, &F);
		if (H==0) break;
		currentHeight=0;
		fatigueFactor = U*(0.01*F);
		fat=0;
		for(int day=1; true; day++){
			currentHeight+=((double)U - fat > 0.0? (double)U - fat : 0.0);
			if (currentHeight>H){
				printf("success on day %d\n", day);
				break;
			}
			fat += fatigueFactor;
			currentHeight -= (double)D;
			if (currentHeight<0){
				printf("failure on day %d\n", day);
				break;
			}
		}
	}
	return 0;
}