#include <cstdio>

int main()
{
    const int n=0, l=1, s=2, o=3;
    int N, M, S, frente, x, y, contador;
    char c, mapa[100][100];
    while(true){
        scanf("%d %d %d", &N, &M, &S);
        if (N==0 && M==0 && S==0) break;
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++){
                scanf(" %c", &c);
                switch(c){
                    case 'N':
                        frente=n;
                        x=i;
                        y=j;
                        mapa[i][j]='.';
                        break;
                    case 'S':
                        frente=s;
                        x=i;
                        y=j;
                        mapa[i][j]='.';
                        break;
                    case 'L':
                        frente=l;
                        x=i;
                        y=j;
                        mapa[i][j]='.';
                        break;
                    case 'O':
                        frente=o;
                        x=i;
                        y=j;
                        mapa[i][j]='.';
                        break;
                    case '.':
                    case '#':
                    case '*':
                        mapa[i][j]=c;
                        break;
                    default: break;
                }
            }
        }
        contador=0;
        for (int i=0; i<S; i++){
            scanf(" %c", &c);
            switch (c){
                case 'F':
                    if (frente == n && x-1 >=0 && mapa[x-1][y]!='#')
                    {
                        x--;
                        if (mapa[x][y]=='*'){
                            contador++;
                            mapa[x][y]='.';
                        }
                    }
                    else if (frente == s && x+1 <N && mapa[x+1][y]!='#')
                    {
                        x++;
                        if (mapa[x][y]=='*'){
                            contador++;
                            mapa[x][y]='.';
                        }
                    }
                    else if (frente == l && y+1 <M && mapa[x][y+1]!='#')
                    {
                        y++;
                        if (mapa[x][y]=='*'){
                            contador++;
                            mapa[x][y]='.';
                        }
                    }
                    else if (frente == o && y-1 >=0 && mapa[x][y-1]!='#')
                    {
                        y--;
                        if (mapa[x][y]=='*'){
                            contador++;
                            mapa[x][y]='.';
                        }
                    }
                    break;
                case 'D':
                    frente++;
                    if (frente>3) frente = 0;
                    break;
                case 'E':
                    frente--;
                    if (frente<0) frente = 3;
            }
        }
        printf("%d\n", contador);
    }
    return 0;
}
