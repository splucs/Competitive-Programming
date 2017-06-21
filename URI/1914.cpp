#include <string>
#include <iostream>

using namespace std;

int main(){
	int QT, x, y;
	cin >> QT;
	string str1, str2, o1, o2;
	for (int i=0; i<QT; i++){
		cin >> str1 >> o1 >> str2 >> o2;
		cin >> x >> y;
		if ((o1=="PAR") == ((x+y)%2==0)) cout << str1 << endl;
		else cout << str2 << endl;
	}
	return 0;
}