#include <iostream>
#include <deque>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

#define pi (atan2(1.0,0.0)*2.0)
#define INF 1.0E25

class point
{
	public:
	point() { x = 0.0; y = 0.0; }
	point( const point& p ) : x( p.x ), y( p.y ) {}
	point( double x, double y ) { this->x = x; this->y = y; }
	friend ostream & operator<<(ostream& os, const point& p) {	os << "(" << p.x << ", " << p.y << ")"; return os; }
	double x;
	double y;
};

bool operator==( const point & a, const point & b ) { return ( a.x == b.x && a.y == b.y ); }
bool cmp_points_x_increasing( const point & a, const point & b ) {	return ( ( a.x != b.x ) ? ( a.x < b.x ) : ( a.y < b.y ) ); }
bool cmp_points_x_decreasing( const point & a, const point & b ) {	return ( ( a.x != b.x ) ? ( a.x > b.x ) : ( a.y > b.y ) ); }

class vec
{
public:
	vec( const point& start, const point& end ) { dx = ( end.x - start.x ); dy = ( end.y - start.y ); }
	vec( double dx, double dy ) { this->dx = dx; this->dy = dy; }
	double length() const { return sqrt( dx*dx + dy*dy ); }
	double direction() const // return a direction angle for vector in the range 0 .. 2pi
	{	double result = atan2 (dy,dx); // returns 0..pi or -pi..0
		if ( result < 0.0 )
			result = 2.0*pi + result; // convert to range 0..2pi
		return result;
	}
	friend double cross( const vec& v, const vec& w ) { return ( v.dx * w.dy - v.dy * w.dx ); }
	friend point operator+( const point& p, const vec& v ) { return point( v.dx+p.x, v.dy+p.y  ); }

	double dx;
	double dy;
};

vec operator-( const point& p, const point& q ) { return vec( q.x - p.x, q.y-p.y ); }

class segment
{
public:
	segment() : ps(), pe() {}
	segment( const point& start, const point& end ) : ps(start), pe(end) {}

	double length() const
	{	double dx = pe.x-ps.x;
		double dy = pe.y-ps.y;
		return sqrt( dx*dx + dy*dy );
	}

	double direction() const // return a direction angle for the segment in the range 0 .. 2pi
	{	double result = atan2 (pe.y-ps.y,pe.x-ps.x); // returns 0..pi or -pi..0
		return ( ( result < 0.0 ) ? (2.0*pi + result) : result ); // convert to range 0..2pi
	}

	double angle( const segment& t ) const  { return t.direction() - direction(); }

	point ps;
	point pe;
};

// Note: the following enumeration was designed for both segments and lines
enum LinesRelationship { NOT_INTERSECTING, INTERSECTING, PARALLEL, COINCIDENT  };

class line
{
public:
	line( const point& a, const point& b ) : pa(a), pb(b) {}
	line( const segment& s ) : pa(s.ps), pb(s.pe) { }
	line( const point& a, const double dir ) 
	{	pa = a;
		pb.x = ( a.x + cos(dir) );
		pb.y = ( a.y + sin(dir) );
	}

	// distance from this line to point p. NOTE: if below this line the distance will be negative if above, positive
	double psuedo_dist_from_line( point & p )
	{	return (pa.x*pb.y + p.x*pa.y + pb.x*p.y - p.x*pb.y - pb.x*pa.y - pa.x*p.y);  // for real distanced divide by (pa-pb).length();
	}
	
	LinesRelationship intersection( const line& ol, point& p )
	{
		double x1 = pa.x; double y1 = pa.y;
		double x2 = pb.x; double y2 = pb.y;
		double x3 = ol.pa.x; double y3 = ol.pa.y;
		double x4 = ol.pb.x; double y4 = ol.pb.y;

		double denom = ((y4 - y3)*(x2 - x1)) - ((x4 - x3)*(y2 - y1));
		double nume_a = ((x4 - x3)*(y1 - y3)) - ((y4 - y3)*(x1 - x3));
		double nume_b = ((x2 - x1)*(y1 - y3)) -  ((y2 - y1)*(x1 - x3));

		if (denom == 0.0)
		{   if (nume_a == 0.0 && nume_b == 0.0) { return COINCIDENT; }
			return PARALLEL;
        }
        double ua = nume_a / denom;
        double ub = nume_b / denom;

		// This conditional is for intersection of segments. Comment out if intersecting lines
        //if ( ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0 )
        //{ // Get the intersection point.
            p.x = ( x1 + ua*(x2 - x1));
            p.y = ( y1 + ua*(y2 - y1));
            return INTERSECTING;
        //}
        return NOT_INTERSECTING;
    }

	double direction() const // return a direction angle for the line in the range 0 .. 2pi
	{	double result = atan2 (pb.y-pa.y,pb.x-pa.x); // returns 0..pi or -pi..0
		if ( result < 0.0 )
			result = 2.0*pi + result; // convert to range 0..2pi
		return result;
	}

	double angle( const line& t ) const { return t.direction() - direction(); }

	point pa;
	point pb;
};

// Class to hold antipodal pairs
class evtype 
{
public:
	evtype() : edge(), vertex() {}
	evtype( const point& a, const point& b, const point& c ) : edge(a,b), vertex(c){}
	double angle( evtype& p ) { return( edge.angle(p.edge)); }
	segment edge;
	point vertex;
};

// Class to hold a parallelogram constructed from antipodal pairs
class pargram {
	
public:
	pargram() : a(), b(), c(), infinite(false) {}
	pargram(evtype& z1, evtype& z2 ) : infinite(false) {
		double z1dir = z1.edge.direction();
		double z2dir = z2.edge.direction();
		LinesRelationship z1z2 = line(z1.edge).intersection( line(z2.edge), a );
		if (z1z2 == PARALLEL) infinite = true; 
		LinesRelationship z1z2v = line(z1.edge).intersection( line(z2.vertex, z2dir), b );
		LinesRelationship z2vz1v = line(z2.vertex, z2dir).intersection( line( z1.vertex, z1dir), c );
	}

	double area() { return (  (infinite) ? INF : ( segment(a,b).length()*segment(b,c).length()*fabs(sin(angle()))) ); }
	double angle() { return( fabs(segment(a,b).angle(segment(b,c)))); }
	point fourth() const { return( point(a) + vec(c.x-b.x,c.y-b.y ) ); }
	
	point a, b, c;
	bool infinite;
};

bool left_turn( const point& a,  const point& b,  const point& c )
{	vec V( a, b ); vec W( b, c );
	return (cross( V, W ) > 0.0);
}

bool right_turn( const point& a,  const point& b,  const point& c )
{	vec V( a, b ); vec W( b, c );
	return (cross( V, W ) < 0.0);
}

// Find the antipodal_pairs from the set of hull points
void antipodal_pairs( vector<evtype>& lap, vector<point>& A ) {
	int i; int j = 1;
	for ( i = 0; i < (int) A.size(); i++ )
	{	vec v( -A[i].x + A[ (i+1)%A.size() ].x, -A[i].y + A[ (i+1)%A.size() ].y );
		while ( left_turn( A[j], A[(j+1)%A.size()], A[(j+1)%(A.size())]+v ) )
			j = (j+1)%A.size();
		lap.push_back( evtype( A[i], A[(i+1)%A.size()], A[j]) );
	}
}

// Simple algorithm for checking all antipodal pair combinations
pargram simple_algorithm( vector<evtype>& lap ) {
	double opt = INF;
	pargram optpar;
	int i, j;
	for ( i = 0; i < (int) lap.size(); i++ ) {
		for ( j=i+1; j < (int) lap.size(); j++ ) {
			evtype z1 = lap[i];
			evtype z2 = lap[j];
			pargram P(z1, z2);
			double a = P.area();

			if ( a < opt ) {
				opt = a;
				optpar = P;
			}
		}
	}
	return optpar;
}

// Linear time algorithm for finding parallelograms after finding the convex hull
// walk around the hull searching for the minimum area paragram
pargram linear_algorithm( vector<evtype>& lap) {
	double opt = 1e25;
	pargram optpar, P;
	int i; int j = 0; 
	evtype z1;
	evtype z2 = lap[j];
	for ( i = 0; i < (int) lap.size(); i++ ) {
		z1 = lap[i];
		if ( i == j ) {
			j = (j+1)%lap.size();
			z2 = lap[j];
		}
		vec v( - z1.edge.ps.x + z1.edge.pe.x, - z1.edge.ps.y + z1.edge.pe.y );
		while ( right_turn( z2.vertex, z2.edge.pe, z2.edge.pe+v)) 
		{	j = (j+1)%(lap.size());
			z2 = lap[j];
		}
		if (! left_turn( z2.vertex, z2.edge.ps, z2.edge.ps+v ) ) {
			pargram P(z1, z2);
			double a = P.area();
			if ( a < opt) {
				opt = a;
				optpar = P;
			}
		}
		if ( ! left_turn( z2.vertex, z2.edge.pe, z2.edge.pe+v ) ) {
			j = (j+1)%lap.size();
			z2 = lap[j];
			pargram P(z1, z2);
			double a = P.area();
			if ( a < opt) {
				opt = a;
				optpar = P;
			}
		}
	}
	return optpar;
}

// Compute upperhull recursively
void upperhull( vector<point> & hull, vector<point> & pts, const point & p1, const point & p2 )
{
	vector<point> ptsabove;

	if ( pts.size() >= 1 )
	{	bool found = false;
		double max = 0.0;
		vector<point>::iterator itmax;
		line hline( p1, p2 );
		for ( vector<point>::iterator it = pts.begin(); it != pts.end(); it++ )
		{	double dist =  hline.psuedo_dist_from_line(*it);
			// Check if above line 
			if (  dist > 0.0  ) 
			{	ptsabove.push_back( *it );
				if ( dist > max )
				{	max = dist;
					itmax = it;
					found = true;
				}
			}
		}
		// only add point to hull if not already in the hull
		if ( found && hull.end() == find(hull.begin(), hull.end(), *itmax ))
		{
			hull.push_back(*itmax);
			upperhull( hull, ptsabove, p1, *itmax );
		    upperhull( hull, ptsabove, *itmax, p2 );
		}
	}
}

// Compute lowerhull recursively (identical approach to upper hull algorithm )
void lowerhull( vector<point> & hull, vector<point> & pts, const point & p1, const point & p2 )
{
	vector<point> ptsbelow;
		
	if ( pts.size() >= 1 )
	{	bool found = false;
		double max = 0.0;
		vector<point>::iterator itmax;
		line hline( p1, p2 );
		for ( vector<point>::iterator it = pts.begin(); it != pts.end(); it++ )
		{	double dist =  hline.psuedo_dist_from_line(*it);
			if ( dist < 0.0 ) 
				ptsbelow.push_back( *it );
			if ( dist < max )
			{	max = dist;
				itmax = it;
				found = true;
			}
		}
		// only add point to hull if not already in the hull
		if ( found && hull.end() == find(hull.begin(), hull.end(), *itmax ))
		{
			hull.push_back(*itmax);
			lowerhull( hull, ptsbelow,  p1, *itmax );
		    lowerhull( hull, ptsbelow,  *itmax, p2 );
		}
	}
}

// Compute the convex hull of a set of points
void quickhull( vector<point> & hull, vector<point> & pts )
{
	// Sort all the points initially by x then y coord
	sort( pts.begin(), pts.end(), cmp_points_x_increasing );

	vector<point> uhull;
	vector<point> lhull;

	// get point 1 and point 2
	point p1 = pts.front();
	pts.erase( pts.begin() );
	point p2 = pts.back();
	pts.pop_back();

	// Compute the upper hull of the set of points
	uhull.push_back(p1);
	upperhull( uhull, pts, p1, p2 );
	uhull.push_back(p2);
	// Sort points in upper hull from small to large x
	sort( uhull.begin(), uhull.end(), cmp_points_x_increasing );

	// Compute the lower hull of the set of points
	lowerhull( lhull, pts, p1, p2 );
	sort( lhull.begin(), lhull.end(), cmp_points_x_decreasing );

	// Take all upper hull points and add them to final hull
	for ( vector<point>::iterator it = uhull.begin(); it != uhull.end(); it++ )
	{	hull.push_back( *it );
	}
	// Take all the lower hull points and add them to final hull
	for ( vector<point>::iterator it = lhull.begin(); it != lhull.end(); it++ )
	{	hull.push_back( *it );
	}
}

int main()
{

	int swarm, swarms, n;
	double x, y;

	cin >> swarms;
	for ( swarm=1; swarm<=swarms; swarm++ )
	{	cin >> n;
		// Read in all the data points
		vector<point> pts;
		while ( n --> 0 )
		{	cin >> x; cin >> y;
			pts.push_back(point(x,y) );
		}
		// 
		vector<point > hull;
		vector<evtype> lap;

		quickhull( hull, pts ); 
		antipodal_pairs( lap, hull );
		pargram opt = simple_algorithm( lap );

		cout << "Swarm " << swarm << " Parallelogram Area: " << fixed << setprecision(4) << opt.area() << endl;
	}
}
