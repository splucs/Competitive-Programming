#include <bits/stdc++.h>
using namespace std;
#define G 9.80665
#define PI 3.14169

int main(){
	int c,l;
	cin>>l>>c;
	double d = sqrt((double)l*l+c*c);
	printf("%.10lf",sqrt(d*PI/G));
}