#include <cstdio>
#include <set>
#include <utility>
#define swap(x, y) {int _x = x; x = y; y = _x;}
using namespace std;

typedef pair<int, int> ii;



int main()
{
	int k, x, y;
	set<ii> ans;
	set<ii>::iterator it;
	while(scanf("%d", &k)!=EOF){
		ans.clear();
		for(x=k+1; x<=2*k; x++){
			if ((k*x)%(x-k)==0){
				y = (k*x)/(x-k);
				if (x>y) swap(x,y);
				ans.insert(ii(x,y));
			}
		}
		printf("%d\n", (int)ans.size());
		for(it = ans.begin(); it!=ans.end(); it++){
			printf("1/%d = 1/%d + 1/%d\n", k, it->second, it->first);
		}
	}
	return 0;
}