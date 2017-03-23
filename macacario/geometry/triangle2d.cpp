struct triangle{
	point a, b, c;
	triangle() { a = b = c = point(); }
	triangle(point _a, point _b, point _c) : a(_a), b(_b), c(_c) {}
	double perimeter() { return dist(a,b) + dist(b,c) + dist(c,a); }
	double semiPerimeter() { return perimeter()/2.0; }
	double area() {
		double s = semiPerimeter(), ab = dist(a,b),
			bc = dist(b,c), ca = dist(c,a);
		return sqrt(s*(s-ab)*(s-bc)*(s-ca));
	}
	double rInCircle() {
		return area()/semiPerimeter();
	}
	circle inCircle() {
		circle ans;
		ans.r = rInCircle();
		if (fabs(ans.r) < EPS) return circle(point(NAN,NAN), NAN);
		line l1, l2;
		double ratio = dist(a, b) / dist(a, c);
		point p = b + ((c-b)*(ratio / (1 + ratio)));
		l1 = pointsToLine(a, p);
		ratio = dist(b, a) / dist(b, c);
		p = a + ((c-a)*(ratio / (1 + ratio)));
		l2 = pointsToLine(b, p);
		ans.c = intersection(l1, l2);
		return ans;
	}
	double rCircumCircle() {
		return dist(a,b)*dist(b,c)*dist(c,a)/(4.0*area());
	}
	circle circumCircle(){
		return pointsToCircle(a,b,c);
	}
	int isInside(point p){
		double u = cross(b-a,p-a)*cross(b-a,c-a);
		double v = cross(c-b,p-b)*cross(c-b,a-b);
		double w = cross(a-c,p-c)*cross(a-c,b-c);
		if (fabs(u) < EPS || fabs(v) < EPS || fabs(w) < EPS) return 1;
		else if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		else return 2;
	} //0 = inside/ 1 = border/ 2 = outside
};

double rInCircle(point a, point b, point c) {
	return triangle(a,b,c).rInCircle();
}

double rCircumCircle(point a, point b, point c) {
	return triangle(a,b,c).rCircumCircle();
}

int isInsideTriangle(point a, point b, point c, point p){
	return triangle(a,b,c).isInside(p);
} //0 = inside/ 1 = border/ 2 = outside