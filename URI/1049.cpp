#include <cstdio>
#include <cstring>
int main()
{
    char a1[50], a2[50], a3[50];
    scanf("%s %s %s", a1, a2, a3);
    if (!strcmp(a1, "vertebrado"))
    {
        if (!strcmp(a2, "ave"))
        {
            if (!strcmp(a3, "carnivoro")) printf("aguia\n");
            else if (!strcmp(a3, "onivoro")) printf("pomba\n");
        }
        else if (!strcmp(a2, "mamifero"))
        {
            if (!strcmp(a3, "herbivoro")) printf("vaca\n");
            else if (!strcmp(a3, "onivoro")) printf("homem\n");
        }
    }
    else if (!strcmp(a1, "invertebrado"))
    {
        if (!strcmp(a2, "inseto"))
        {
            if (!strcmp(a3, "herbivoro")) printf("lagarta\n");
            else if (!strcmp(a3, "hematofago")) printf("pulga\n");
        }
        else if (!strcmp(a2, "anelideo"))
        {
            if (!strcmp(a3, "onivoro")) printf("minhoca\n");
            else if (!strcmp(a3, "hematofago")) printf("sanguessuga\n");
        }
    }
    return 0;
}
