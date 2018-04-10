#include <bits/stdc++.h>
using namespace std;

double A;
double x[3], y[3], z[3];

void rotatex(double theta) {
  for(int i = 0; i < 3; i++) {
    double tx = x[i];
    double ty = y[i]*cos(theta) - z[i]*sin(theta);
    double tz = y[i]*sin(theta) + z[i]*cos(theta);
    x[i] = tx; y[i] = ty; z[i] = tz;
  }
}

void rotatey(double theta) {
  for(int i = 0; i < 3; i++) {
    double tx = x[i]*cos(theta) + z[i]*sin(theta);
    double ty = y[i];
    double tz = -x[i]*sin(theta) + z[i]*cos(theta);
    x[i] = tx; y[i] = ty; z[i] = tz;
  }
}

void rotatez(double theta) {
  for(int i = 0; i < 3; i++) {
    double tx = x[i]*cos(theta) - y[i]*sin(theta);
    double ty = x[i]*sin(theta) + y[i]*cos(theta);
    double tz = z[i];
    x[i] = tx; y[i] = ty; z[i] = tz;
  }
}

int main() {
  int T;
  double s2 = sqrt(2.0);
  scanf("%d", &T);
  for(int caseNo = 1; caseNo <= T; caseNo++) {
    x[0] = 0.5; y[0] = 0.0; z[0] = 0.0;
    x[1] = 0.0; y[1] = 0.5; z[1] = 0.0;
    x[2] = 0.0; y[2] = 0.0; z[2] = 0.5;
    scanf("%lf", &A);
    if (A <= s2) {
      double theta = asin(A/s2) - M_PI/4.0;
      rotatex(theta);
    }
    else {
      rotatex(M_PI/4.0);
      double theta = M_PI/2.0 - asin(A/sqrt(3.0)) + asin(1.0/sqrt(3.0));
      rotatez(theta);
    }
    printf("Case #%d:\n", caseNo);
    for(int i = 0; i < 3; i++) {
      printf("%.15f %.15f %.15f\n", x[i], y[i], z[i]);
    }
  }
  return 0;
}