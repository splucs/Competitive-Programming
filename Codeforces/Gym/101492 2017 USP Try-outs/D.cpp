#include <bits/stdc++.h>
#define INF 1e+180
#define MAXN 100009
using namespace std;
#define EPS 1e-20

class CHTrick {
private:
	vector<double> m, n;
	vector<double> p;
	bool maxCH;
	double ans;
public:
	CHTrick() { ans = -INF; }
	double inter(double nm, double nn, double lm, double ln) {
		double x = (ln - nn) / (nm - lm);
		ans = max(ans, nm*x + nn);
		return x;
	}
	void pushinv(double nm, double nn) {
		while (!p.empty()) {
			if (fabs(nm - m.back()) < EPS && nn < n.back()) return;
			if (fabs(nm - m.back()) > EPS && p.back() <	inter(1.0/nm, nn, 1.0/m.back(), n.back())) break;
			m.pop_back(); n.pop_back(); p.pop_back();
		}
		p.push_back(p.empty() ? -INF : inter(1.0/nm, nn, 1.0/m.back(), n.back()));
		m.push_back(nm); n.push_back(nn);
	}
	void push(double nm, double nn) {
		while (!p.empty()) {
			if (fabs(nm - m.back()) < EPS && nn < n.back()) return;
			if (fabs(nm - m.back()) > EPS && p.back() <	inter(nm, nn, m.back(), n.back())) break;
			m.pop_back(); n.pop_back(); p.pop_back();
		}
		p.push_back(p.empty() ? -INF : inter(nm, nn, m.back(), n.back()));
		m.push_back(nm); n.push_back(nn);
	}
	double query() {
		return ans;
	}
};

typedef pair<double, double> dd;
dd arr[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &arr[i].first, &arr[i].second);
		arr[i].second *= -1;
	}
	
	CHTrick cht;
	
	sort(arr, arr+N);
	cht = CHTrick();
	for(int i=0; i<N; i++) {
		cht.push(arr[i].first, arr[i].second);
	}
	double maxy = cht.query();
	
	for(int i=0; i<N; i++) {
		arr[i].second *= -1;
		arr[i].first *= -1;
	}
	sort(arr, arr+N);
	cht = CHTrick();
	for(int i=0; i<N; i++) {
		cht.push(arr[i].first, arr[i].second);
	}
	double miny = -cht.query();
	
	for(int i=0; i<N; i++) {
		arr[i].second *= -1;
		arr[i].first *= -1;
		arr[i].second /= -arr[i].first;
	}
	sort(arr, arr+N);
	cht = CHTrick();
	for(int i=0; i<N; i++) {
		cht.pushinv(arr[i].first, arr[i].second);
	}
	double maxx = cht.query();
	
	for(int i=0; i<N; i++) {
		arr[i].second *= -1;
		arr[i].first *= -1;
	}
	sort(arr, arr+N);
	cht = CHTrick();
	for(int i=N-1; i>=0; i--) {
		cht.pushinv(arr[i].first, arr[i].second);
	}
	double minx = -cht.query();
	
	printf("%.5f %.5f %.5f %.5f\n", minx, miny, maxx, maxy);
	
	return 0;
	
}