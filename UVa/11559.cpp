#include <cstdio>

int main()
{
	int N, B, H, W, min, price, numbeds;
	bool canstayhere;
	while(scanf("%d %d %d %d", &N, &B, &H, &W)!=EOF){
		min=600000;
		for(int h=0; h<H; h++){
			scanf("%d", &price);
			canstayhere=false;
			for(int i=0; i<W; i++){
				scanf("%d", &numbeds);
				if (numbeds>=N) canstayhere=true;
			}
			if (canstayhere && price<min) min=price;
		}
		if (min*N>B) printf("stay home\n");
		else printf("%d\n", min*N);
	}
	return 0;
}