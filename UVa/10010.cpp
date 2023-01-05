#include <cstdio>
#include <cstring>
#define MAXN 60

int main(){
	int T, n, m, k, l, t;
	char text[MAXN][MAXN], str[MAXN];
	bool found = false;
	scanf("%d", &T);
	while(T-->0){
		if (found) printf("\n");
		scanf(" %d %d", &n, &m);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				scanf(" %c", &text[i][j]);
				if (text[i][j]>='A' && text[i][j]<='Z') text[i][j] += 'a'-'A';
			}
		}
		scanf("%d", &k);
		while(k-->0){
			scanf(" %s", str);
			found = false;
			l = strlen(str);
			for(int i=0; i<l; i++){
				if (str[i]>='A' && str[i]<='Z') str[i] += 'a'-'A';
			}
			for(int i=0; i<n && !found; i++){
				for(int j=0; j<m && !found; j++){
					for(t=0; !found && t<l && i+t<n; t++){
						if (text[i+t][j]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && i-t>=0; t++){
						if (text[i-t][j]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && j+t<m; t++){
						if (text[i][j+t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && j-t>=0; t++){
						if (text[i][j-t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && i+t<n && j+t<m; t++){
						if (text[i+t][j+t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && i+t<n && j-t>=0; t++){
						if (text[i+t][j-t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && i-t>=0 && j+t<m; t++){
						if (text[i-t][j+t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
					for(t=0; !found && t<l && i-t>=0 && j-t>=0; t++){
						if (text[i-t][j-t]!=str[t]) break;
					}
					found = ((t==l) || found);
					if (found) {
						printf("%d %d\n", i+1, j+1);
						break;
					}
				}
			}
		}
	}
	return 0;
}