#include <cstdio>

int main()
{
    int x;
    while (scanf("%d", &x)!=EOF){
        if (x==2002){
            printf("Acesso Permitido\n");
            break;
        }
        else printf("Senha Invalida\n");
    }
    return 0;
}

