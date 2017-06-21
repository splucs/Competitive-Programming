#include <stdio.h>
#include <set>
#include <algorithm>

int main(){
    while (true)
    {
        int na, nb, x;
        scanf("%d %d", &na, &nb);
        if (na==0 && nb==0)
            break;
        std::set<int> a;
        std::set<int> b;
        for (int i=0; i<na; i++)
        {
            scanf ("%d", &x);
            a.insert(x);
        }
        for (int i=0; i<nb; i++)
        {
            scanf ("%d", &x);
            b.insert(x);
        }
        int conta = 0, contb = 0;

        std::set<int>::iterator it;
        for (it = a.begin(); it!=a.end(); it++)
        {
            if (!b.count(*it))
                conta++;
        }
        for (it = b.begin(); it!=b.end(); it++)
        {
            if (!a.count(*it))
                contb++;
        }
        printf ("%d\n", std::min(conta, contb));
    }
    return 0;
}
