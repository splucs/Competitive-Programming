#include <cstdio>
#include <map>
#include <cstring>
#include <string>
using namespace std;

typedef struct letra{
    int c;
} letra;

letra operator *(letra a, letra b){
    letra res;
    bool neg = ((a.c<0)!=(b.c<0));
    a.c = (a.c<0?-a.c:a.c);
    b.c = (b.c<0?-b.c:b.c);
    if (a.c == 1 && b.c== 1) res.c = 1;
    else if (a.c == 1 && b.c== 2) res.c = 2;
    else if (a.c == 1 && b.c== 3) res.c = 3;
    else if (a.c == 1 && b.c== 4) res.c = 4;
    else if (a.c == 2 && b.c== 1) res.c = 2;
    else if (a.c == 2 && b.c== 2) res.c = -1;
    else if (a.c == 2 && b.c== 3) res.c = 4;
    else if (a.c == 2 && b.c== 4) res.c = -3;
    else if (a.c == 3 && b.c== 1) res.c = 3;
    else if (a.c == 3 && b.c== 2) res.c = -4;
    else if (a.c == 3 && b.c== 3) res.c = -1;
    else if (a.c == 3 && b.c== 4) res.c = 2;
    else if (a.c == 4 && b.c== 1) res.c = 4;
    else if (a.c == 4 && b.c== 2) res.c = 3;
    else if (a.c == 4 && b.c== 3) res.c = -2;
    else if (a.c == 4 && b.c== 4) res.c = -1;
    if (neg) res.c*=-1;
    return res;
}

int main()
{
    /*char a, b, cd;
    letra al, bl, cl;
    scanf(" %c %c", &a, &b);
    printf("a=%c b=%c\n", a, b);
    if (a=='1') al.c=1;
    if (a=='i') al.c=2;
    if (a=='j') al.c=3;
    if (a=='k') al.c=4;
    if (b=='1') bl.c=1;
    if (b=='i') bl.c=2;
    if (b=='j') bl.c=3;
    if (b=='k') bl.c=4;
    cl=al*bl;
    if (cl.c==1) printf("1\n");
    if (cl.c==-1) printf("-1\n");
    if (cl.c==2) printf("i\n");
    if (cl.c==-2) printf("-i\n");
    if (cl.c==3) printf("j\n");
    if (cl.c==-3) printf("-j\n");
    if (cl.c==4) printf("k\n");
    if (cl.c==-4) printf("-k\n");*/
    long long int L, X, T, len, x;
    letra mult;
    char seq[10005];
    letra l[10005];
    bool used[12], certo;
    long long int last[12], delta;
    scanf("%lld", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%lld %lld", &L, &X);
        scanf(" %s", seq);
        len = strlen(seq);
        for (int i=0; i<len; i++){
            if (seq[i]=='i') l[i].c=2;
            if (seq[i]=='j') l[i].c=3;
            if (seq[i]=='k') l[i].c=4;
        }
        mult.c = 1;
        int k=0;
        certo=true;


        for (int i=0; i<10; i++){
            used[i]=false;
        }
        used[5+1]=true;
        while(certo){
            if (k==L){
                k=0;
                X--;
                if (used[5+mult.c] || X==0){
                    certo=false;
                    break;
                }
                used[5+mult.c]=true;
            }
            mult = mult*l[k++];
            if (mult.c==2) break;
        }

        mult.c=1;
        for (int i=0; i<10; i++){
            used[i]=false;
        }
        while(certo){
            if (k==L){
                k=0;
                X--;
                if (used[5+mult.c] || X==0){
                    certo=false;
                    break;
                }
                used[5+mult.c]=true;
            }
            mult = mult*l[k++];
            if (mult.c==3) break;
        }

        mult.c=1;
        for (int i=0; i<10; i++){
            used[i]=false;
        }
        while(certo){
            if (k==L){
                k=0;
                X--;
                if (used[5+mult.c] || X==0){
                    certo=false;
                    break;
                }
                used[5+mult.c]=true;
            }
            mult = mult*l[k++];
            if (mult.c==4) break;
        }

        mult.c=1;
        for (int i=0; i<10; i++){
            last[i]=-1;
        }
        while(certo){
            if (k==L){
                k=0;
                //printf("X = %d\n", X);
                X--;
                if (last[5+mult.c]!=-1){
                    delta = last[5+mult.c]-X;
                    X%=delta;
                }
                last[5+mult.c] = X;
            }
            if (X==0) break;
            mult = mult*l[k++];
        }
        if (mult.c!=1) certo = false;

        if (certo) printf("Case #%d: YES", caso);
        else printf("Case #%d: NO", caso);
        if (caso<T) printf("\n");
    }
    return 0;
}
