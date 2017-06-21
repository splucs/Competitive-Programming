#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
	int N, nFruits, found, totalFruits=0;
	double weight, totalWeight=0;
	string fruits;
	scanf("%d", &N);
	for (int day=1; day<=N; day++){
		scanf("%lf ", &weight);
		totalWeight+=weight;
		getline (cin,fruits);
		nFruits=1;
		found = -1;
		found=fruits.find(' ', found+1);
		while(found!=string::npos){
			nFruits++;
			found=fruits.find(' ', found+1);
		}
		totalFruits+=nFruits;
		printf("day %d: %d kg\n", day, nFruits);
	}
	printf("%.2f kg by day\n", totalFruits/(double)N);
	printf("R$ %.2f by day\n", totalWeight/N);
	return 0;
}