#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    while (true)
    {
        unsigned int a, b, c=0;
        if (scanf("%u %u", &a, &b)==EOF)break;
        for (int counter=1; a>0 || b>0; counter*=2)
        {
            if (a%2!=b%2) c+=counter;
            a/=2;
            b/=2;
        }
        cout << c<< endl;
    }
    return 0;
}
