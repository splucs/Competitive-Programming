#include <stdio.h>

bool c[100000];

int main() {
    int a, b;

    while(scanf("%d %d" , &a, &b) != EOF)
    {
        for (int i = 0; i <= b; ++i)
        {
            c[i] = false;
        }

        bool first = false;
        for (int i = 1; i <= a; ++i)
        {
            int n;
            scanf("%d", &n);

            if (c[n] == false) {
                c[n] = true;

                if (!first) {
                    printf("%d", n);
                    first = true;
                }
                else {
                    printf(" %d", n);
                }
            }
        }

        printf("\n");
    }
}
