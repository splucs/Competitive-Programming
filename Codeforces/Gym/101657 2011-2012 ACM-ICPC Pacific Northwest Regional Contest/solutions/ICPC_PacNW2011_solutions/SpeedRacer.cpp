#include <cstdlib>
#include <iostream>
using namespace std ;
/*
   (a v^4 + b v^3 + c v^2 + d v) * (m / v) = t
   a v^3 + b v^2 + c v + d = t/m
 */
int main(int argc, char *argv[]) {
  double a, b, c, d, m, t ;
  cout.setf(ios::fixed,ios::floatfield) ;
  cout.precision(2) ;
  while (1) {
    cin >> a >> b >> c >> d >> m >> t ;
    if (cin.fail())
       break ;
    if (a < 0 || b < 0 || c <= 0 || d <= 0 || m <= 0 || t <= 0 ||
        a > 1000 || b > 1000 || c > 1000 || d > 1000 || m > 1000 || t > 1000) {
       cerr << "Bad input" << endl ;
       exit(10) ;
    }
    double high = (t/m-d)/c ;
    double low = 0 ;
    for (int i=0; i<100; i++) {
      double v = (high + low) / 2.0 ;
      double desc = a*v*v*v+b*v*v+c*v+d-t/m ;
      if (desc < 0) {
        low = v ;
      } else {
        high = v ;
      }
    }
    double test = 100 * low ;
    test -= (int)test ;
    if (test < 1e-6 || test > 1-1e-6) {
       cerr << "Failed precision guarantee" << endl ;
       exit(10) ;
    }
    low -= 0.005 ; // change round to truncate
    cout << low << endl ;
  }
}
