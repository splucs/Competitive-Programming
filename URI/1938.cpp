#include <cstdio>
#include <algorithm>
using namespace std;

typedef struct point{
	int x, y;
} point;

bool compx(const point a, const point b){
	return a.x<b.x;
}

int main()
{
	int N, max, min, res=0;
	scanf("%d", &N);
	point points[3009];
	for(int i=0; i<N; i++){
		scanf("%d %d", &points[i].x, &points[i].y);
	}
	sort(points, points+N, &compx);
	for(int i=0; i<N; i++){
		max=200000000, min=-200000000;
		for(int j=i+1; j<N; j++){
			if(points[j].y>points[i].y && points[j].y<=max){
				res++;
				max = points[j].y;
			}
			else if(points[j].y<points[i].y && points[j].y>=min){
				res++;
				min = points[j].y;
			}
		}
	}
	printf("%d\n", res);
	return 0;
}