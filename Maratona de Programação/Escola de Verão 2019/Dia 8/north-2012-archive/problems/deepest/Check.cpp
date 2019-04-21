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
/* Checker                                                        */
/*                                                                */
/* Author               Oleg Davydov                              */
/******************************************************************/

#include <testlib.h>

int d, x, y;

const long double eps = 3e-10;

bool parseOutput( InStream &s, TResult wa, TResult pe ) {
  std::string ans = s.readLine();
  s.seekEof();
  if (ans == "Impossible")
    return false;
  if (ans == "Single staircase") {
    if (x * x + y * y == d * d)
      return true;
    quitf(wa, "single staircase fail");
  }
  double x1, y1, z1;
  int r = sscanf(ans.c_str(), "%lf %lf %lf", &x1, &y1, &z1);
  if (r != 3)
    quitf(pe, "cannot parse output: '%s'", ans.c_str());
  if (z1 < 0 - eps || z1 > d + eps)
    quitf(wa, "intermediate lobby must be underground, above main lobby");
  long double d1 = sqrt(x1 * x1 + y1 * y1);
  x1 -= x, y1 -= y;
  long double d2 = sqrt(x1 * x1 + y1 * y1);
  long double h1 = d - z1;
  long double h2 = z1;
  if (fabsl(h1 - d1) > eps)
    quitf(wa, "lower staircase fail");
  if (fabsl(h2 - d2) > eps)
    quitf(wa, "upper staircase fail");
  return true;
}

int main( int argc, char **argv ) {
  setName("icpc.2012.neerc.qf-nothern.deep");
  registerTestlibCmd(argc, argv);
  x = inf.readInt();
  y = inf.readInt();
  d = inf.readInt();

  bool ja = parseOutput(ans, _fail, _fail);
  bool pa = parseOutput(ouf, _wa, _pe);

  if (ja && !pa)
    quitf(_wa, "jury found solution, but participant failed");
  if (!ja && pa)
    quitf(_fail, "participant found solution, but jury failed");

  if (ja && pa)
    quitf(_ok, "yes");
  if (!ja && !pa)
    quitf(_ok, "impossible");

  quitf(_fail, "wait, what? how did you get in my house?");
}

