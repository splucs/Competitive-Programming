#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std ;
struct point {
   double x, y ;
   point(double x_, double y_) : x(x_), y(y_) {}
   point() : x(0), y(0) {}
   double mag() { return sqrt(x*x+y*y) ; }
} ;
double side(const point &a, const point &b, const point &p) {
   return (b.x-a.x)*(p.y-a.y)-(b.y-a.y)*(p.x-a.x) ;
}
// use of pair<> here gives us free operator<().
typedef pair<double, int> sortable ;
double cos(const point &a, const point &b) {
  double dx = b.x - a.x ;
  double dy = b.y - a.y ;
  return dx / sqrt(dx * dx + dy * dy) ;
}
double abssin(point &a, point &b) {
  return fabs(side(point(0, 0), a, b) / a.mag() / b.mag()) ;
}
/*
 *   If the last three points here constitute a right turn, then eliminate
 *   the middle point.
 */
void checkforleft(vector<point> &hull) {
  while (1) {
    if (hull.size() < 3)
      return ;
    size_t s = hull.size() ;
    if (side(hull[s-3], hull[s-1], hull[s-2]) > 0)
      return ;
    hull[s-2] = hull[s-1] ;
    hull.pop_back() ;
  }
}
void calchull(const vector<point> &pts, vector<point> &hull) {
  int s = 0 ;
  for (size_t i=1; i<pts.size(); i++)
    if (pts[i].y < pts[s].y ||
        (pts[i].y == pts[s].y && pts[i].x < pts[s].x))
      s = i ;
  vector<sortable> v ;
  for (size_t i=0; i<pts.size(); i++)
    if (i != s)
      v.push_back(make_pair(cos(pts[s], pts[i]), i)) ;
  sort(v.begin(), v.end()) ;
  hull.push_back(pts[s]) ;
  for (size_t ii=0; ii<v.size(); ii++) {
    int i = v[ii].second ;
    hull.push_back(pts[i]) ;
    checkforleft(hull) ;
  }
}
/*
 *   If we rest the hull on a particular line segment, what is the height
 *   of the hull?  We do this with a walk around the hull.
 *   We use the fact that side() calculates the cross product, which
 *   is the area of the parallelogram, which is the height multiplied
 *   by the magnitude of the base vector.
 */
void calcheights(const vector<point> &hull, vector<double> &h) {
  int at = 2 ;
  for (size_t i=0; i<hull.size(); i++) {
    point a = hull[i] ;
    point b = (i + 1 >= hull.size() ? hull[0] : hull[i+1]) ;
    double atv = -side(a, b, hull[at]) ;
    while (1) {
      int at2 = at + 1 ;
      if (at2 >= hull.size())
        at2 = 0 ;
      double tv = -side(a, b, hull[at2]) ;
      if (tv > atv) {
        at = at2 ;
        atv = tv ;
      } else
        break ;
    }
    h.push_back(atv/sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y))) ;
  }
}
void docase(int kase) {
  int n = 0 ;
  cin >> n ;
  vector<point> pts ;
  for (int i=0; i<n; i++) {
    double x=0, y=0 ;
    cin >> x >> y ;
    pts.push_back(point(x, y)) ;
  }
  vector<point> hull ;
  calchull(pts, hull) ;
  double r = 0 ;
  if (hull.size() >= 3) {
    r = 1e99 ;
    vector<double> h ;
    calcheights(hull, h) ;
    for (size_t i=0; i+1 < hull.size(); i++) {
      point a = hull[i] ;
      point b = hull[i+1] ;
      point ab = point(b.x-a.x, b.y-a.y) ;
      double abh = h[i] ;
      for (size_t j=i+1; j<hull.size(); j++) {
        point c = hull[j] ;
        point d = (j + 1 >= hull.size() ? hull[0] : hull[j+1]) ;
        point cd = point(d.x-c.x, d.y-c.y) ;
        double cdh = h[j] ;
        double s = abssin(ab, cd) ;
        if (s > 0) {
          double t = abh * cdh / s ;
          if (t < r)
            r = t ;
        }
      }
    }
  }
  cout << "Swarm " << kase << " Parallelogram Area: " << r << endl ;
}
int main(int, char *[]) {
  int nswarms = 0 ;
  cin >> nswarms ;
  cout.precision(4) ;
  cout << fixed ;
  for (int i=1; i<=nswarms; i++)
    docase(i) ;
}
