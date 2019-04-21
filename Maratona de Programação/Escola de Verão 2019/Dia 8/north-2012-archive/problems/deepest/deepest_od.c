/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem D. Deepest Station                                     */
/*                                                                */
/* Original idea        Oleg Davydov                              */
/* Problem statement    Oleg Davydov                              */
/* Test set             Oleg Davydov                              */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Oleg Davydov                              */
/******************************************************************/

#include <assert.h>
#include <math.h>
#include <stdio.h>

int main() {
  int d, x, y;
  assert(freopen("deepest.in", "r", stdin));
  assert(freopen("deepest.out", "w", stdout));

  assert(scanf("%d%d%d", &x, &y, &d) == 3);
  if (x * x + y * y > d * d)
    puts("Impossible");
  else if (x * x + y * y == d * d)
    puts("Single staircase");
  else {
    long double dist = sqrt(0.0 + x * x + y * y);
    long double r = 0.5 * (dist + d);
    long double z1 = d - r;
    // here we use that (x, y) ? (0, 0)
    long double x1 = x * r / dist;
    long double y1 = y * r / dist;
    printf("%.20lf %.20lf %.20lf\n", (double)x1, (double)y1, (double) z1);
  }

  return 0;
}

