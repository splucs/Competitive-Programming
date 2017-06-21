#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char line[MAXN], pline[MAXN], word[MAXN];
int len, nprob, nteams, wrong[309][30], nsol[309], pen[309], R[309];
bool solved[309][30];
typedef pair<bool, int> ii;

int main() {
    freopen("ideal.in", "r", stdin);
    freopen("ideal.out", "w", stdout);

    bool problems = false;
    int cur = 0;
    while(!feof(stdin)) {
		gets(line);
		len = strlen(line);
        //printf("%s\n", line);
		scanf(" ");
        if (!problems){
            problems = true;
            for(int i=0; i<len; i++){
                if (line[i] != '-') problems = false;
            }
            if(problems){
                int i=0;
                nprob = 0;
                while(pline[i]!='T') i++;
                while(pline[i]!=' ') i++;
                while(pline[i]!='='){
                    if (pline[i] != ' ') nprob++;
                    i++;
                }
            }
        }
        else{
			queue<ii> q;
			int state = 0;
			for(int i=0, j=0; i<=len; i++){
				if (i == len || line[i] == ' '){
					if (j==i){
						j++;
						continue;
					}
					int sub = 0;
					if (line[j] == '+'){
						state = 0;
						if (line[j+1] >= '0' && line[j+1] <= '9'){
							sscanf(line+j+1, "%d", &sub);
							q.push(ii(true, sub));
						}
						else if (j+1 == i){
							q.push(ii(true, sub));
						}
					}
					if (line[j] == '-'){
						state = 0;
						int sub;
						if (line[j+1] >= '0' && line[j+1] <= '9'){
							sscanf(line+j+1, "%d", &sub);
							q.push(ii(false, sub));
						}
					}
					if (line[j] == '.' && j+1==i){
						state = 0;
						q.push(ii(false, sub));
					}
					else if (line[j] >= '0' && line[j] <= '9' && (int)q.size() >= nprob){
						state++;
						if (state == 1) sscanf(line+j, "%d", &nsol[cur]);
						if (state == 2) sscanf(line+j, "%d", &pen[cur]);
						if (state == 3) sscanf(line+j, "%d", &R[cur]);
					}
					j=i+1;
				}
			}
			while((int)q.size() > nprob) q.pop();
			int j=0;
			while(!q.empty()){
				solved[cur][j] = q.front().first;
				wrong[cur][j] = q.front().second;
				q.pop();
				j++;
			}
			
			/*for(j=0; j<nprob; j++){
                printf("%d(%d) ", wrong[cur][j], solved[cur][j]);
            }
            printf("%d %d %d, state = %d\n", nsol[cur], pen[cur], R[cur], state);*/
			cur++;
        }

        strcpy(pline, line);
    }
	
	nteams = cur;
	double I[30], totI = 0.0;
	double vain = 0.0, oversim = 0.0, even = 0.0, unsol = 0.0;
	
	for(int j=0; j<nprob; j++) {
		I[j] = 0;
		int nosolve = 0;
		int nsolved = 0;
		for(int i=0; i<nteams; i++){
			if (solved[i][j]){
				int x = nosolve;
				for(int k=i-1; k>=0; k--){
					if (!solved[k][j] && nsol[i] == nsol[k] && pen[k]==pen[i]) x--;
				}
				I[j] = max(I[j], x*1.0/nteams);
				nsolved++;
			}
			else nosolve++;
		}
		if (nsolved == 0) unsol += 1.0/nprob;
		totI += I[j];
	}
	
	for(int i=0; i<nteams; i++){
		if (nsol[i] == 0) vain += 1.0/nteams;
		if (nsol[i] == nprob) oversim += 1.0/nteams;
		if (i > 0 && nsol[i-1] > nsol[i]) even += (nsol[i-1] - nsol[i] - 1.0) / nprob;
	}
	
	double negi = 1.03*vain + 3.141*oversim + 2.171*even + 1.414*unsol + totI/nprob;
	
	printf("Vainness = %.3f\n", vain);
	printf("Oversimplification = %.3f\n", oversim);
	printf("Evenness = %.3f\n", even);
	printf("Unsolvability = %.3f\n", unsol);
	for(int j=0; j<nprob; j++)
		printf("Instability %d = %.3f\n", j+1, I[j]);
	printf("Negidealness = %.3f\n", negi);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
