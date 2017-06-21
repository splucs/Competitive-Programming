#include <cstdio>
int main()
{
    double N1, N2, N3, N4, media;
    scanf("%lf %lf %lf %lf", &N1, &N2, &N3, &N4);
    media = (2.0*N1 + 3.0*N2 + 4.0*N3 + N4)/10.0;
    printf("Media: %.1f\n", media);
    if (media >=7) printf("Aluno aprovado.\n");
    else if (media<5) printf("Aluno reprovado.\n");
    else{
        double exame, mediaf;
        printf("Aluno em exame.\n");
        scanf("%lf", &exame);
        printf("Nota do exame: %.1f\n", exame);
        mediaf = (media+exame)/2.0;
        if (mediaf >=5) printf("Aluno aprovado.\n");
        else printf("Aluno reprovado.\n");
        printf("Media final: %.1f\n", mediaf);
    }
    return 0;
}
