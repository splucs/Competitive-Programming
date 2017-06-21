#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	int s[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
	int N, leds;
	string numb;
	cin>> N;
	while (N-->0){
		cin>> numb;
		leds=0;
		for (int i = 0; i < numb.size(); ++i)
		{
			leds+=s[numb[i]-'0'];
		}
		printf("%d leds\n", leds);
	}
	return 0;
}