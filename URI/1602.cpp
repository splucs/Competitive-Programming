#include <stdio.h>
 #include <utility>
  #include <set>
   #include <math.h>

    using std::set;
 using std::pair;
 using std::make_pair;

 int c[2010000];
 bool prime[1010000];
 bool hiperprimo[2010000];
 int primes[101000];
 int p = 1;

 bool isPrime(int n) {
     if (n < 0) return isPrime(-n);
     if (n < 5 || n % 2 == 0 || n % 3 == 0) return (n == 2 || n == 3);

     int maxP=sqrt(n) + 2;

     for (int p = 5; p < maxP; p+=6) if((n%p==0||n%(p+2)==0)) return false;
     return true;
 }

 int main() {
     int a, b;

     for (int n = 1; n*n <= 2200000; ++n) {
        if (isPrime(n))
        {
            prime[n] = true;
            primes[p] = n;
            ++p;
        }
     }

    for (int n = 1; n < p; ++n)
    {
        long long primo = primes[n];
        hiperprimo[(int)primo] = true;


        for (int m = 1; m < p; ++m)
        {
            long long pprimo = primo;

            int primoAtual = primes[m] - 1;
            for (int i = 1; i < primoAtual; ++i)
            {
                pprimo *= primo;
                if (pprimo > 2010000) break;
            }

            if (pprimo > 2010000) continue;
            hiperprimo[(int)pprimo] = true;
        }
    }

    c[2] = 1;
    for (int i = 3; i < 2010000; ++i)
    {
        if (hiperprimo[i] || isPrime(i)) c[i] = c[i-1] + 1;
        else c[i] = c[i-1];
    }

     while(scanf("%d" , &a) != EOF)
     {
        printf("%d\n", c[a]);
     }
 }
