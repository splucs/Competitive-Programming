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
	double rCircumCircle() {
		return dist(a,b)*dist(b,c)*dist(c,a)/(4.0*area());
	}
	point normalVector() {
		return cross(y-x, z-x).normalized();
	}
	int isInside(point p) {
		point n = normalVector();
		double u = proj(cross(b-a,p-a), n).normalized()*proj(cross(b-a,c-a), n).normalized();
		double v = proj(cross(c-b,p-b), n).normalized()*proj(cross(c-b,a-b), n).normalized();
		double w = proj(cross(a-c,p-c), n).normalized()*proj(cross(a-c,b-c), n).normalized();
		if (u > 0.0 && v > 0.0 && w > 0.0) return 0;
		else if (u < 0.0 || v < 0.0 || w < 0.0) return 2;
		else return 1;
	} //0 = inside/ 1 = border/ 2 = outside
	int isProjInside(point p) {
		return isInside(p + proj(a-p, normalVector()));
	} //0 = inside/ 1 = border/ 2 = outside
};

double rInCircle(point a, point b, point c) {
	return triangle(a,b,c).rInCircle();
}

double rCircumCircle(point a, point b, point c) {
	return triangle(a,b,c).rCircumCircle();
}

int isProjInsideTriangle(point a, point b, point c, point p) {
	return triangle(a,b,c).isProjInside(p);
} //0 = inside/ 1 = border/ 2 = outside