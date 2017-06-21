#include <stdio.h>
#include <utility>
#include <set>

using std::set;
using std::pair;
using std::make_pair;

int c[1010][1010];

int main() {
    int a, b;

    while(scanf("%d %d" , &a, &b) != EOF)
    {
        for (int i = 1; i <= a; ++i)
        {
            for (int j = 1; j <= b; ++j)
            {
                int d;
                scanf("%d", &d);
                c[i][j] = d;
            }
        }

        set< pair< int, int > > picos;

        for (int i = 1; i <= a; ++i)
        {
            for (int j = 1; j <= b; ++j)
            {
                bool pico = true;

                for (int x = -1; x < 2; ++x)
                {
                    if (i + x > 0 && i + x <= a)
                    {
                        for (int y = -1; y < 2; ++y)
                        {
                            if (x != 0 || y != 0)
                            {
                                if (j + y > 0 && j + y <= b)
                                {
                                    if (c[i][j] <= c[i+x][j+y]) pico = false;
                                }
                            }
                        }
                    }

                }

                if (pico)
                {
                    picos.insert(make_pair(i, j));
                }
            }
        }

        if (picos.size() == 0)
        {
            printf("-1\n\n");
        }
        else
        {
            for( auto x : picos) {
                printf("%d %d\n", x.first, x.second);
            }
            printf("\n");
        }
    }
}
