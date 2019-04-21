#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long seed = 0;
int lcg_rand( int a, int b ) {
  unsigned r;
  assert(a < b);
  r = (seed >> 16) % (unsigned)(b - a + 1);
  seed = seed * 17239 + 6666;
  return a + r;
}

int main( int argc, char **argv ) {
  int i, limit, x, y, d;
  if (argc != 3) {
    fprintf(stderr, "usage: %s <limit> <seed>\n", argv[0]);
    return 1;
  }
  i, limit = atoi(argv[1]);
  seed = atoi(argv[2]);
  for (i = 0; i < 100; i++)
    lcg_rand(0, 1);

  x = 0, y = 0;
  do {
    x = lcg_rand(-limit, limit);
    y = lcg_rand(-limit, limit);
  } while (x == 0 && y == 0);
  d = lcg_rand(106, limit);

  printf("%d %d %d\n", x, y, d);

  return 0;
}
