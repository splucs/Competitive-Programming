#include <cstdio>
#include <cstring>
#define MAXN 109
#define INF (1<<30)

enum Type {END, DELETE, INSERT, REPLACE, NEXT};

struct command{
	int value;
	Type type;
	int ni, nj;
	int i, j;
	char carac; 
};

command dp[MAXN][MAXN];
int n, m;
char str1[MAXN], str2[MAXN];

command DP(const int i, const int j){
	if (dp[i][j].value>=0) return dp[i][j];
	command res, aux;
	if (i==n && j==m){
		res.value = 0;
		res.type = END;
		return  dp[i][j] = res;
	}
	if (i==n){
		res.type = INSERT;
		res.carac = str2[j];
		res.ni = i; res.nj = j+1;
		res.value = DP(res.ni, res.nj).value + 1;
		return dp[i][j] = res;
	}
	if (j==m){
		res.type = DELETE;
		res.ni = i+1; res.nj = j;
		res.value = DP(res.ni, res.nj).value + 1;
		return dp[i][j] = res;
	}
	res.value = INF;
	if (str1[i]==str2[j]){
		aux.type = NEXT;
		aux.ni = i+1; aux.nj = j+1;
		aux.value = DP(aux.ni, aux.nj).value;
		if (aux.value < res.value) res = aux;
	}
	aux.type = DELETE;
	aux.ni = i+1; aux.nj = j;
	aux.value = DP(aux.ni, aux.nj).value + 1;
	if (aux.value < res.value) res = aux;
	aux.type = INSERT;
	aux.carac = str2[j];
	aux.ni = i; aux.nj = j+1;
	aux.value = DP(aux.ni, aux.nj).value + 1;
	if (aux.value < res.value) res = aux;
	aux.type = REPLACE;
	aux.carac = str2[j];
	aux.ni = i+1; aux.nj = j+1;
	aux.value = DP(aux.ni, aux.nj).value + 1;
	if (aux.value < res.value) res = aux;
	return dp[i][j] = res;
}

int main(){
	command now;
	int skip, ni, nj, nsteps=-1, aux;
	char c;
	while(true){
		aux = c = 0;
		while(true){
			if(scanf("%c", &c)==EOF) break;
			if(c=='\n') break;
			str1[aux++]=c;
		}
		str1[aux]='\0';
		aux = c = 0;
		while(true){
			if(scanf("%c", &c)==EOF) break;
			if(c=='\n') break;
			str2[aux++]=c;
		}
		str2[aux]='\0';
		if (str1[0]=='\0' && str2[0]=='\0') break;
		if(nsteps>=0) printf("\n");
		//printf("|%s|\n|%s|\n", str1, str2);
		n = strlen(str1);
		m = strlen(str2);
		for(int i=0; i<=n; i++){
			for(int j=0; j<=m; j++){
				dp[i][j].value=-1;
			}
		}
		skip = 0;
		ni = nj = 0;
		now = DP(0,0);
		printf("%d\n", now.value);
		nsteps=1;
		while(now.type!=END){
			if (now.type == INSERT){
				printf("%d Insert %d,%c\n", nsteps++, ni+skip+1, now.carac);
				skip++;
			}
			if (now.type == REPLACE){
				printf("%d Replace %d,%c\n", nsteps++, ni+skip+1, now.carac);
			}
			if (now.type == DELETE){
				printf("%d Delete %d\n", nsteps++, ni+skip+1);
				skip--;
			}
			ni = now.ni;
			nj = now.nj;
			now = dp[ni][nj];
		}
	}
	return 0;
}