#include <cstdio>

int main()
{
	int Q, V, fav=0, con=0;
	scanf("%d", &Q);
	for(int i=0; i<Q; i++){
		scanf("%d", &V);
		if(V==0) fav++;
		else con++;
	}
	if(fav>con) printf("Y\n");
	else printf("N\n");
	return 0;
}