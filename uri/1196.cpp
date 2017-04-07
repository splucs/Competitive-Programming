#include <cstdio>
#include <map>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	char keyboard[] = {' ', ' ',
						'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 
						'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\',
						'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'',
						'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
	map<char, char> previous;
	for (int i = 1; i < 49; ++i)
	{
		previous[keyboard[i]]=keyboard[i-1];
	}
	string setence;
	while(getline(cin, setence)){
		for (int i = 0; i < setence.size(); ++i)
		{
			setence[i]=previous[setence[i]];
		}
		printf("%s\n", setence.c_str());
	}
	return 0;
}