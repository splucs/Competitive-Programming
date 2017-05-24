#include <bits/stdc++.h>
using namespace std;

int main()
{
	int h, m;
	char ch[10], cm[10];
	while(scanf("%d:%d", &h, &m)!=EOF){
		for(int i=0; i<10; i++){
			if (h & (1<<i)) ch[i] = 'o';
			else ch[i] = ' ';
			if (m & (1<<i)) cm[i] = 'o';
			else cm[i] = ' ';
		}
		printf(" ____________________________________________\n");
		printf("|                                            |\n");
		printf("|    ____________________________________    |_\n");
		printf("|   |                                    |   |_)\n");
		printf("|   |   8         4         2         1  |   |\n");
		printf("|   |                                    |   |\n");
		printf("|   |   %c         %c         %c         %c  |   |\n", ch[3], ch[2], ch[1], ch[0]);
		printf("|   |                                    |   |\n");
		printf("|   |                                    |   |\n");
		printf("|   |   %c     %c     %c     %c     %c     %c  |   |\n", cm[5], cm[4], cm[3], cm[2], cm[1], cm[0]);
		printf("|   |                                    |   |\n");
		printf("|   |   32    16    8     4     2     1  |   |_\n");
		printf("|   |____________________________________|   |_)\n");
		printf("|                                            |\n");
		printf("|____________________________________________|\n");
		printf("\n");
	}
	return 0;
}