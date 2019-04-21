/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem J. Juggle with Criteria                                */
/*                                                                */
/* Original idea        Mikhail Dvorkin                           */
/* Problem statement    Mikhail Dvorkin                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Sergey Kopeliovich                        */
/******************************************************************/

/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2012.11.01
 */

#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back 
#define sz(a) (int)(a).size()

const int N = 7;

struct state
{
  int a[5], p[N];
};

char s[5 + 1];
int n0, tn, n, u[N], p[N], f[N];
int is[243], a[243][N], b[243][N];
vector <state> v;

void go( int i, int n )
{
  if (i == n)
  {
    state s;

    s.a[0] = 0;
    forn(i, n)
      forn(j, i)
        if (p[j] > p[i])
          s.a[0]++;

    s.a[1] = 0;
    forn(i, n - 1)
      if (p[i] > p[i + 1])
        s.a[1]++;

    s.a[2] = 0;
    forn(i, n)
    {
      f[i] = 0;
      forn(j, i)
        if (p[j] < p[i])
          f[i] = max(f[i], f[j]);
      s.a[2] = max(s.a[2], ++f[i]);
    }

    int bad = 0;
    s.a[3] = 0;
    forn(i, n)
    {
      int j = i;
      while (j + 1 < n && p[j + 1] > p[j])
        j++;
      s.a[3] = max(s.a[3], j - i + 1);
      if (n0 > n && j - i + 1 == s.a[3] && j + 1 == n)
        bad = 1;
    }
    
    s.a[4] = 0;
    forn(i, n)
      if (p[i] == i)
        s.a[4]++;              

    memcpy(s.p, p, sizeof(p));
    if (!bad)
      v.pb(s);
    return;
  }
  forn(x, n)
    if (!u[x])
    {
      u[x] = 1, p[i] = x;
      go(i + 1, n);
      u[x] = 0;
    }
}

void gen( int n )
{
  go(0, n);
}

const char *str = "<>=";

inline int F( int x, int y )
{
  return x < y ? 0 : (x > y ? 1 : 2);
}

void out( int *a, int n )
{
  int k = n - min(n, N);
  forn(i, min(n, N))
    printf("%d ", a[i] + 1);
  forn(i, k)
    printf("%d ", n - i);
  puts("");
}

int main()
{
  #define NAME "juggle"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  
  scanf("%d%d", &tn, &n), n0 = n;
  gen(min(n, N));
  forn(i, sz(v))
    forn(j, sz(v))
    {
      int x = 0;
      forn(k, 5)
        x = x * 3 + F(v[i].a[k], v[j].a[k]);
      if (!is[x])
      {
        is[x] = 1;
        memcpy(a[x], v[i].p, sizeof(a[x]));
        memcpy(b[x], v[j].p, sizeof(b[x]));
      }
    }

  while (tn--)
  {
    scanf("%s", s);

    int q = 0;
    forn(i, 5)
      q = q * 3 + (strchr(str, s[i]) - str);
    if (!is[q])
      puts("Not exists");
    else
    {
      puts("Exists");
      out(a[q], n);
      out(b[q], n);
    }
  }
  return 0;
}

