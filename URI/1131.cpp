#include <cstdio>

int main()
{
    int grenal=0, vit1=0, vit2=0, emp=0, p1, p2;
    do{
        grenal++;
        scanf("%d %d", &p1, &p2);
        if (p1>p2) vit1++;
        else if (p1==p2) emp++;
        else vit2++;
        printf("Novo grenal (1-sim 2-nao)\n");
        scanf("%d", &p1);
    }while(p1==1);
    printf("%d grenais\n", grenal);
    printf("Inter:%d\n", vit1);
    printf("Gremio:%d\n", vit2);
    printf("Empates:%d\n", emp);
    if (vit1>vit2) printf("Inter venceu mais\n");
    else if (vit1<vit2) printf("Gremio venceu mais\n");
    else printf("Nao houve vencedor\n");
    return 0;
}
