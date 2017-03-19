#include <cstdio>
#include <vector>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

typedef long long int ll;

class CHTrick {
private:
	vector<ll> m, n;
	vector<double> p;
	bool maxCH;
public:
	CHTrick(bool _maxCH) { maxCH = _maxCH; }
	void clear() {
		m.clear(); n.clear(); p.clear();
	}
	double inter(double nm, double nn, double lm, double ln) {
		return (ln - nn) / (nm - lm);
	}
	void push(ll nm, ll nn) {
		while (!p.empty() &&
			((nm == m.back() && (maxCH ? -1 : 1)*nn <= (maxCH ? -1 : 1)*n.back()) ||
				p.back() >= inter(nm, nn, m.back(), n.back()))) {
			m.pop_back(); n.pop_back(); p.pop_back();
		}
		p.push_back(p.empty() ? -INF : inter(nm, nn,
			m.back(), n.back()));
		m.push_back(nm); n.push_back(nn);
	}
	ll query(ll x) {
		if (p.empty()) return (maxCH ? -1 : 1)*INF;
		double dx = (double)x;
		ll high = p.size() - 1, low = 0, mid;
		if (dx >= p[high]) return m[high] * x + n[high];
		while (high > low + 1) {
			mid = (high + low) / 2;
			if (dx < p[mid]) high = mid;
			else low = mid;
		}
		return m[low] * x + n[low];
	}
};