#include <cstdio>
#include <cstring>
#define MAXN 100009
#define MAXM 100000

int main()
{
	char name1[MAXM], name2[MAXM], seq1[MAXM], seq2[MAXM];
	int p1=0, p2=0, ns1=0, ns2=0, ss1, ss2, pos1, pos2, rounds;
	char c='1';
	while(scanf("%c", &c), c!=':'){
		name1[ns1++]=c;
	}
	name1[ns1]='\0';
	scanf(" %s", seq1);
	ss1 = strlen(seq1);
	c = '1';
	while(scanf("%c", &c), c!=':'){
		name2[ns2++]=c;
	}
	name2[ns2]='\0';
	scanf(" %s ", seq2);
	ss2 = strlen(seq2);
	pos1=pos2=0;
	for(rounds=1; rounds<=MAXN; rounds++){
		if (seq1[p1]=='R'){
			if (seq2[p2]=='S'){
				pos1++;
				pos2--;
			}
			if (seq2[p2]=='P'){
				pos1--;
				pos2++;
			}
		}
		if (seq1[p1]=='P'){
			if (seq2[p2]=='R'){
				pos1++;
				pos2--;
			}
			if (seq2[p2]=='S'){
				pos1--;
				pos2++;
			}
		}
		if (seq1[p1]=='S'){
			if (seq2[p2]=='P'){
				pos1++;
				pos2--;
			}
			if (seq2[p2]=='R'){
				pos1--;
				pos2++;
			}
		}
		p1++;
		if (p1==ss1) p1=0;
		p2++;
		if (p2==ss2) p2=0;
		if (pos1==5 || pos2==5) break;
	}
	if(pos1>pos2)  printf("%d\n%s", rounds, name1);
	else  printf("%d\n%s", rounds, name2);
	return 0;
}