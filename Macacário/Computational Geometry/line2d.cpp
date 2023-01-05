struct line {
	double a, b, c;
	line() { a = b = c = NAN;}
	line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
};

line pointsToLine(point p1, point p2) {
	line l;
	if (fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS) {
		l.a = l.b = l.c = NAN;
	}
	else if (fabs(p1.x - p2.x) < EPS) {
		l.a = 1.0; l.b = 0.0; l.c = -p1.x;
	}
	else {
		l.a = -(p1.y - p2.y) / (p1.x - p2.x);
		l.b = 1.0;
		l.c = -(l.a * p1.x) - p1.y;
	}
	return l;
}

bool areParallel(line l1, line l2) {
	return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {
	return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS);
}

point intersection(line l1, line l2) {
	if (areParallel(l1, l2)) return point(NAN, NAN);
	point p;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
	else p.y = -(l2.a * p.x + l2.c);
	return p;
}

point projPointToLine(point u, line l) {
	point a, b;
	if (fabs(l.b-1.0)<EPS) {
		a = point(-l.c/l.a, 0.0);
		b = point(-l.c/l.a, 1.0);
	}
	else{
		a = point(0, -l.c/l.b);
		b = point(1, -(l.c+1.0)/l.b);
	}
	return a + proj(u-a, b-a);
}
