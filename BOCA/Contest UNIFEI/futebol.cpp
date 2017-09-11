#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int year[MAXN];
wstring buffer;
map<wstring, int> mp;
vector<pair<int, wstring> > clas;

int main() {
	int N;
	cin >> N;
	for(int y=0; y<N; y++) {
		cin >> year[y];
		for(int j=0, i; j<20; j++) {
			wstring club;
			while(true) {
				cin >> buffer;
				if (buffer == "-") break;
				club = club + buffer;
			}
			cin >> p;
			//wprintf(L"%s fez %d pontos em %d\n", club.c_str(), p, year[y]);
			if (mp.count(club)) mp[club] += p;
			else mp[club] = p;
		}
	}
	for(map<string, int>::iterator it = mp.begin(); it != mp.end(); it++) {
		clas.push_back(make_pair(MAXN-it->second, it->first));
	}
	sort(year, year+N);
	cout << "Os 10 melhores do ano de " << year[0];
	for(int y=1; y<N-1; y++) cout << ", " << year[y];
	cout << " e " << year[N-1] << ":\n";
	sort(clas.begin(), clas.end());
	for(int i=0; i<10; i++) {
		cout << i+1 << clas[i].second << MAXN-clas[i].first << endl;
	}
	return 0;
}