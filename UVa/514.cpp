#include <cstdio>
#include <stack>
using namespace std;

int main()
{
	int N, n, a, i;
	stack<int> s;
	while(scanf("%d", &N), N){
		while(true){
			while(!s.empty()) s.pop();
			n=1;
			for(i=0; i<N; i++){
				scanf("%d", &a);
				if (a==0) break;
				if (!s.empty() && s.top()==a){
					s.pop();
					continue;
				}
				while(n<=N && n!=a) s.push(n++);
				n++;
			}
			if (i<N) break;
			if (s.empty() && n==N+1) printf("Yes\n");
			else printf("No\n");
		}
		printf("\n");
	}
	return 0;
}