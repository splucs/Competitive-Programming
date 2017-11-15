#include <bits/stdc++.h>
using namespace std;
#define MAXN 10

char style[MAXN][100];
char sample[MAXN][100];

int p,q,lines[MAXN];

void compute(int r,int c,int s){
	int n,j,openr,openc,opens;
	char car;
	openr = openc=opens = 0;
	int cnt = 0;
	
	for (int i=0;i<q;i++){
		n = strlen(sample[i]);
		j = 0;
		
		cnt = openr*r+openc*c+opens*s;
		if (lines[i]==0)lines[i] = cnt;
		else if (lines[i]!=cnt)lines[i] = -1;
		
		while (j<n){
			car = sample[i][j++];
			if (car=='(')openr++;
			else if (car==')')openr--;
			else if (car=='[')opens++;
			else if (car==']')opens--;
			else if (car=='{')openc++;
			else if (car=='}')openc--;
		}
	}
}

bool solve(int r,int c,int s){
	int n,j,openr,openc,opens;
	char car;
	openr = openc=opens = 0;
	
	for (int i=0;i<p;i++){
		n = strlen(style[i]);
		int cnt = 0;
		j = 0;
		while (j<n&&style[i][j]=='.')cnt++,j++;
		if (cnt!=openr*r+openc*c+opens*s)return false;
		while (j<n){
			car = style[i][j++];
			if (car=='(')openr++;
			else if (car==')')openr--;
			else if (car=='[')opens++;
			else if (car==']')opens--;
			else if (car=='{')openc++;
			else if (car=='}')openc--;
		}
	}
	return true;
}

int main(){
	while (scanf("%d%d",&p,&q)&&p!=0){
		for (int i=0;i<p;i++)scanf("%s",&style[i]);
		for (int i=0;i<q;i++)scanf("%s",&sample[i]);
		
		memset(lines,0,sizeof(lines));
		
		for (int r=1;r<=20;r++){
			for (int c=1;c<=20;c++){
				for (int s=1;s<=20;s++){
					if (solve(r,c,s))compute(r,c,s);
				}	
			}
		}printf("%d",lines[0]);
		for (int i=1;i<q;i++)printf(" %d",lines[i]);
		printf("\n");
	}
}