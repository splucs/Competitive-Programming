#include <cstdio>
#include <cstring>

int main()
{
    int T, S, s[1009], len, Namigos, Nempe;
    char c[1009];
    scanf("%d", &T);
    int caso =1;
    for (; caso<=T; caso++){
        scanf("%d", &S);
        scanf(" %s", c);
        len = strlen(c);
        for (int i=0; i<len; i++){
            s[i]=c[i]-'0';
        }
        Namigos=0;
        Nempe=0;
        for (int i=0; i<len; i++){
            if (Nempe<i && s[i]>0){
                Namigos += i-Nempe;
                Nempe=i;
            }
            Nempe+=s[i];
        }
        printf("Case #%d: %d", caso, Namigos);
        if (caso<T) printf("\n");
    }
    return 0;
}
