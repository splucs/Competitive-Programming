#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
size_t memsize ;
using namespace std ;
struct point {
   int x, y ;
   point(int x_, int y_) : x(x_), y(y_) {}
   point() : x(0), y(0) {}
} ;
struct lineseg {
   lineseg(const point &p1, const point &p2) : a(p1), b(p2) {}
   lineseg() : a(), b() {}
   bool crosses(const lineseg &l2) const {
      if (min(a.x, b.x) > max(l2.a.x, l2.b.x) ||
          max(a.x, b.x) < min(l2.a.x, l2.b.x) ||
          min(a.y, b.y) > max(l2.a.y, l2.b.y) ||
          max(a.y, b.y) < min(l2.a.y, l2.b.y))
         return 0 ;
      return l2.side(a) * l2.side(b) <= 0 && side(l2.a) * side(l2.b) <= 0 ;
   }
   int side(const point &p) const {
      int d = (b.x-a.x)*(p.y-a.y)-(b.y-a.y)*(p.x-a.x) ;
      if (d < 0)
         return -1 ;
      else if (d > 0)
         return 1 ;
      else
         return 0 ;
   }
   point a, b ;
} ;
int h, w, sq, sqm ;
vector<lineseg> walls ;
struct state {
   point p, a ;
   state(point p_) : p(p_), a(0,0) {}
   state() : p(0,0), a(0,0) {}
   bool legal() const {
      return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h &&
             a.x >= -sq && a.x <= sq && a.y >= -sq && a.y <= sq ;
   }
   int index() const {
      return a.x + sq + sqm * (a.y + sq + sqm * (p.x + w * p.y)) ;
   }
   bool nextstate(int dx, int dy) {
      a.x += dx ;
      a.y += dy ;
      point oldp = p ;
      p.x += a.x ;
      p.y += a.y ;
      if (!legal())
         return 0 ;
      lineseg ls(oldp, p) ;
      for (size_t i=0; i<walls.size(); i++)
         if (ls.crosses(walls[i]))
            return 0 ;
      return 1 ;
   }
} ;
point start, end ;
int dx[] = { 0, 1, -1, 0, 0 } ;
int dy[] = { 0, 0, 0, 1, -1 } ;
unsigned char *seen ;
int searchfrom(const point &start, const point &end) {
   if (seen)
      free(seen) ;
   seen = (unsigned char *)calloc(memsize, sizeof(unsigned char)) ;
   state startstate(start) ;
   vector<state> thislev ;
   thislev.push_back(startstate) ;
   seen[startstate.index()] = 1 ;
   for (int d=1; ; d++) {
      if (thislev.size() == 0)
         break ;
      vector<state> nextlev ;
      for (int i=0; i<(int)thislev.size(); i++) {
         for (size_t j=0; j<sizeof(dx)/sizeof(dx[0]); j++) {
            state s = thislev[i] ;
            if (s.nextstate(dx[j], dy[j])) {
               int ind = s.index() ;
               if (seen[ind] == 0) {
                  seen[ind] = 2 + j ;
                  if (s.a.x == 0 && s.a.y == 0 &&
                      s.p.x == end.x && s.p.y == end.y)
                     return d ;
                  nextlev.push_back(s) ;
               }
            }
         }
      }
      swap(thislev, nextlev) ;
   }
   cerr << "No solution" << endl ;
   exit(10) ;
}
void onetest() {
   int nwalls = 0 ;
   cin >> w >> h >> start.x >> start.y >> end.x >> end.y ;
   cin >> nwalls ;
   sq = 1 ;
   while (sq * sq <= w || sq * sq <= h)
      sq++ ;
   sqm = 2 * sq + 1 ;
   memsize = h * w * (size_t)(sqm * sqm) ;
   walls.clear() ;
   for (int i=0; i<nwalls; i++) {
      lineseg line ;
      cin >> line.a.x >> line.a.y >> line.b.x >> line.b.y ;
      walls.push_back(line) ;
   }
   if (cin.fail())
      exit(0) ;
   cout << searchfrom(start, end) << endl ;
}
int main(int argc, char *argv[]) {
   while (1)
      onetest() ;
}
