#include <bits/stdc++.h>
using namespace std;
#define ALFA 256
#define MAXN 2009

char S[MAXN];
int T, N, index[ALFA];

int main()
{
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf(" %s", S);
		N = strlen(S);
		memset(&index, 0, sizeof ALFA);
		vector<int> ans;
		for(int i=0; i<N; i++) {
			index[S[i]]++;
		}
		//6
		while(index['X'] > 0) {
			index['S']--;
			index['I']--;
			index['X']--;
			ans.push_back(6);
		}
		//0
		while(index['Z'] > 0) {
			index['Z']--;
			index['E']--;
			index['R']--;
			index['O']--;
			ans.push_back(0);
		}
		//2
		while(index['W'] > 0) {
			index['T']--;
			index['W']--;
			index['O']--;
			ans.push_back(2);
		}
		//4
		while(index['U'] > 0) {
			index['F']--;
			index['O']--;
			index['U']--;
			index['R']--;
			ans.push_back(4);
		}
		//5
		while(index['F'] > 0) {
			index['F']--;
			index['I']--;
			index['V']--;
			index['E']--;
			ans.push_back(5);
		}
		//8
		while(index['G'] > 0) {
			index['E']--;
			index['I']--;
			index['G']--;
			index['H']--;
			index['T']--;
			ans.push_back(8);
		}
		//7
		while(index['S'] > 0) {
			index['S']--;
			index['E']--;
			index['V']--;
			index['E']--;
			index['N']--;
			ans.push_back(7);
		}
		//3
		while(index['H'] > 0) {
			index['T']--;
			index['H']--;
			index['R']--;
			index['E']--;
			index['E']--;
			ans.push_back(3);
		}
		//9
		while(index['I'] > 0) {
			index['N']--;
			index['I']--;
			index['N']--;
			index['E']--;
			ans.push_back(9);
		}
		//1
		while(index['N'] > 0) {
			index['O']--;
			index['N']--;
			index['E']--;
			ans.push_back(1);
		}
		for(int i=0; i<ALFA; i++){
			if(index[i] != 0) printf("Error! %c fault %d\n", i, index[i]);
		}
		sort(ans.begin(), ans.end());
		printf("Case #%d: ", caseNo);
		for(int i=0; i<(int)ans.size(); i++) {
			printf("%d", ans[i]);
		}
		printf("\n");
	}
	return 0;
}