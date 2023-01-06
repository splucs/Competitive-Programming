/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem L. Log Analysis                                        */
/*                                                                */
/* Original idea        Georgiy Korneev                           */
/* Problem statement    Georgiy Korneev                           */
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

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

struct seg
{
  int x, len;

  seg() { }
  seg( int _x, int _len ) : x(_x), len(_len) { }
};

const int maxN = (int)5e4;
const int M = 300;
const int L = (2 * maxN) / M;

int q, tn, is[26];
seg mem[2][4 * maxN], *s = mem[0], *t = mem[1];

struct part
{
  int sn, len, all;
  seg *s;

  void calc()
  {
    len = all = 0;
    forn(i, sn)
      len += s[i].len, all |= 1 << s[i].x;
  }
};

int pn = 0;
part p[2 * M];

void rebuild()
{
  tn = 0;
  forn(i, pn)
    forn(j, p[i].sn)
      if (p[i].s[j].len > 0)
        s[tn++] = p[i].s[j];
  forn(i, tn)
    t[i] = s[i];
  pn = 0;

  for (int pos = 0; pos < tn; pos += p[pn - 1].sn)
  {
    p[pn].s = t + pos;
    p[pn].sn = min(L, tn - pos);
    p[pn++].calc();
  }
}

int split( int ind )
{
  int pos = 0, sum = 0;
  while (pos < pn && sum + p[pos].len <= ind)
    sum += p[pos++].len;
  if (sum == ind)
    return pos;

  for (int i = pn; i > pos; i--)
    p[i] = p[i - 1];

  int j = 0;
  part &P = p[pos];
  while (j < P.sn && sum + P.s[j].len <= ind)
    sum += P.s[j++].len;

  if (sum == ind)
  {
    p[pos + 1].s = p[pos].s + j;
    p[pos + 1].sn -= j;
    p[pos].sn = j;
  }
  else
  {
    int old = tn;
    p[pos + 1].s = t + tn;
    p[pos + 1].sn -= j;
    p[pos].sn = j + 1;
    forn(k, p[pos + 1].sn)
      t[tn++] = p[pos].s[j + k];
    p[pos].s[j].len = ind - sum;
    t[old].len -= ind - sum;
  }
  p[pos].calc();  
  p[pos + 1].calc();  
  pn++;
  return pos + 1;
}

int main()
{
  #define NAME "log"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d", &q); 
  while (q--)
  {
    int ind, n;
    char ch;
    scanf(" %c", &ch);

    if (ch == '+')
    {
      scanf("%d%d %c", &ind, &n, &ch), ind--;
      ch -= 'a';
      int pos = split(ind);
      for (int i = pn++; i > pos; i--)
        p[i] = p[i - 1];
      t[tn] = seg(ch, n);
      p[pos].sn = 1;
      p[pos].s = t + tn++;
      p[pos].calc();
    }
    else if (ch == '-')
    {
      scanf("%d%d", &ind, &n), ind--;
      int l = split(ind);
      int r = split(ind + n);
      for (int i = l; i + r - l < pn; i++)
        p[i] = p[i + r - l];
      pn -= r - l;
    }
    else
    {
      scanf("%d%d", &ind, &n);
      ind--, n -= ind;
      int l = split(ind);
      int r = split(ind + n);
      int res = 0;
      while (l < r)
        res |= p[l++].all;

      int cnt = 0;
      forn(i, 26)
        cnt += (res >> i) & 1;
      printf("%d\n", cnt);
    }

    if (tn >= 4 * maxN - L || pn >= 2 * M - 6)
      rebuild();
  }
  return 0;
}
