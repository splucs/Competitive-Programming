#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

typedef vector<double> VD;

// -- from Stanford ACM team notebook --
double EPS = 1e-12;

struct PT { 
    double x, y; 
    PT() {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator +(const PT &p)  const { return PT(x+p.x, y+p.y); }
    PT operator -(const PT &p)  const { return PT(x-p.x, y-p.y); }
    PT operator *(double c)     const { return PT(x*c,   y*c  ); }
    PT operator /(double c)     const { return PT(x/c,   y/c  ); }

    bool operator<(const PT &rhs)  const { return make_pair(y,x) < make_pair(rhs.y,rhs.x);  }
    bool operator==(const PT &rhs) const { return make_pair(y,x) == make_pair(rhs.y,rhs.x); }
};

double dot(PT p, PT q)         { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)       { return dot(p-q,p-q); }
double cross(PT p, PT q)       { return p.x*q.y-p.y*q.x; }
double area2(PT a, PT b, PT c) { return cross(a,b) + cross(b,c) + cross(c,a); }

PT ProjectPointLine(PT a, PT b, PT c) {
    return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

double DistancePointLine(PT a, PT b, PT c) {
    return sqrt(dist2(c, ProjectPointLine(a, b, c)));
}

void ConvexHull(vector<PT> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<PT> up, dn;
    for (int i = 0; i < pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
}
// -- end excerpt from Stanford ACM team notebook --

int main() {
    int swarms;
    cin >> swarms;
    for (int swarm = 0; swarm < swarms; ++swarm) {
        int n;
        cin >> n;
        vector<PT> pts;
        for (int i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            pts.push_back(PT(x, y));
        }

        ConvexHull(pts);
        VD heights(pts.size());
        for (size_t i = 0; i < pts.size(); ++i)
            for (size_t j = 0; j < pts.size(); ++j)
                heights[i] = max(heights[i], DistancePointLine(pts[i], pts[(i + 1) % pts.size()], pts[j]));

        double min_area = numeric_limits<double>::infinity();
        vector<PT> ans;
        for (size_t i = 0; i < pts.size(); ++i) {
            for (size_t j = i+1; j < pts.size(); ++j) {
                PT p1 = pts[i], q1 = pts[(i + 1) % pts.size()];
                PT p2 = pts[j], q2 = pts[(j + 1) % pts.size()];
                PT e1 = q1-p1, e2 = q2-p2;
                double sin_theta = sin(acos(dot(e1, e2) / sqrt(dot(e1, e1) * dot(e2, e2))));
                if (sin_theta <= EPS) continue;
                double area = heights[i] * heights[j] / sin_theta;
                min_area = min(min_area, area);
            }
        }
        cout << "Swarm " << (swarm+1) << " Parallelogram Area: " << fixed << setprecision(4) << min_area << endl;
    }
    return 0;
}
