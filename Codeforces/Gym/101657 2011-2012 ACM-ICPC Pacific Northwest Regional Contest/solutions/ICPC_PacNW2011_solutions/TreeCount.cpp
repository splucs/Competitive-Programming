#include <iostream>
#include <iomanip>
using namespace std ;
const int MAXN = 1427 ;
const int LOGMAXN = 22 ; // log base phi of MAXN, or something in excess
long long a[MAXN+1][LOGMAXN+1] ;
long long t[MAXN+1] ;
int main(int, char**) {
   a[0][0] = a[1][1] =1 ;
   t[0] = t[1] = 1 ;
   int mind = 1 ;
   for (int n=2; n<=MAXN; n++) {
      long long alln = 0 ;
      for (int d=mind; ; d++) {
         long long s = 0 ;
         int havesome = 0 ;
         for (int i=0; i<n; i++) {
            s += a[i][d-1] * a[n-1-i][d-1] ;
            if (d > 1)
               s += a[i][d-2] * a[n-1-i][d-1] +
                    a[i][d-1] * a[n-1-i][d-2] ;
            if (s)
               havesome = 1 ;
            s %= 1000000000 ;
         }
         if (havesome == 0) {
            if (d == mind)
               mind++ ;
            else
               break ;
         }
         s %= 1000000000 ;
         a[n][d] = s ;
         alln += s ;
      }
      t[n] = alln % 1000000000 ;
   }
   int n ;
   while (1) {
      cin >> n ;
      if (cin.fail())
         break ;
      cout << setfill('0') << setw(9) << t[n] << endl ;
   }
}
