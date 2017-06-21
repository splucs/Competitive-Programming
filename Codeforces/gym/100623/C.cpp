#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

char board[MAXN][MAXN];
int n, r, c;

int main(){
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);

    scanf("%d %d %d", &n, &r, &c);
    memset(&board, '.', sizeof board);
    board[0][0] = '#';
    n--;
    int full = 1;
    for(int i=1, j=1; i<r && j<c && n > 0;){
        if (n > 0){
            board[i][0] = '#';
            i++;
            n--;
            full++;
        }
        if (n > 0){
            board[0][j] = '#';
            j++;
            n--;
            full++;
        }
    }
    if (full %2 != 0) full++;
    full /= 2;
    for(int i=0; i<r && n>0; i++){
        for(int j=0; j<c && n>0; j++){
            if (board[i][j] != '#'){
                board[i][j] = '#';
                n--;
            }
        }
    }
    printf("%d\n", full);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            printf("%c", board[i][j]);
        }
        printf("\n", full);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}