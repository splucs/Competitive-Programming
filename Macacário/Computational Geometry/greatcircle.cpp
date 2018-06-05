#include <cstdio>
#include <cmath>

double gcTheta(double pLat, double pLong, double qLat, double qLong) {
	pLat *= acos(-1.0) / 180.0; pLong *= acos(-1.0) / 180.0; // convert degree to radian
	qLat *= acos(-1.0) / 180.0; qLong *= acos(-1.0) / 180.0;
	return acos(cos(pLat)*cos(pLong)*cos(qLat)*cos(qLong) +
		cos(pLat)*sin(pLong)*cos(qLat)*sin(qLong) +
		sin(pLat)*sin(qLat));
}

double gcDistance(double pLat, double pLong, double qLat, double qLong, double radius) {
	return radius*gcTheta(pLat, pLong, qLat, qLong);
}