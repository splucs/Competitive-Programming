#include <cstdio>
int main(){
    int numA, numB, qA, qB;
    double precoA, precoB, total;
    scanf("%d %d %lf %d %d %lf", &numA, &qA, &precoA, &numB, &qB, &precoB);
    total = precoA*qA + precoB*qB;
    printf ("VALOR A PAGAR: R$ %.2f\n", total);
    return 0;
}
