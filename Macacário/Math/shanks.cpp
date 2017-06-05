#include <cstdio>
#include <map>
using namespace std;

template <typename T>
T solve (T a, T b, T m) {
	T n = (T) sqrt (m + .0) + 1;
	T an = 1;
	for (T i=0; i<n; ++i)
		an = (an * a) % m;
	map<T,T> vals;
	for (T i=1, cur=an; i<=n; ++i) {
		if (!vals.count(cur))
			vals[cur] = i;
		cur = (cur * an) % m;
	}
	for (T i=0, cur=b; i<=n; ++i) {
		if (vals.count(cur)) {
			T ans = vals[cur] * n - i;
			if (ans < m)
				return ans;
		}
		cur = (cur * a) % m;
	}
	return -1;
}
