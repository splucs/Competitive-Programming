#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct team{
	int num;
	int nsolved;
	int time;
	bool submitted;
	bool solved[10];
	int attempt[10];
};

bool comp(team a, team b){
	if (a.submitted!=b.submitted) return a.submitted;
	else if (a.nsolved!=b.nsolved) return a.nsolved > b.nsolved;
	else if (a.time!=b.time) return a.time < b.time;
	else return a.num < b.num;
}

int main(){
	int N, c, p, t;
	scanf(" %d ", &N);
	char str[100], r;
	vector<team> vec;
	vec.resize(109);
	while(N-->0){
		for(int i=0; i<(int)vec.size(); i++){
			vec[i].num=i;
			vec[i].nsolved=0;
			vec[i].time=0;
			vec[i].submitted = false;
			memset(&vec[i].solved, false, sizeof vec[i].solved);
			memset(&vec[i].attempt, 0, sizeof vec[i].attempt);
		}
		while(gets(str) && strlen(str)>4){
			sscanf(str, " %d %d %d %c", &c, &p, &t, &r);
			vec[c].submitted = true;
			if (vec[c].solved[p]) continue;
			if (r=='I'){
				vec[c].attempt[p]++;
			}
			if (r=='C'){
				vec[c].nsolved++;
				vec[c].solved[p] = true;
				vec[c].time += t + 20*vec[c].attempt[p];
			}
		}
		sort(vec.begin(), vec.end(), &comp);
		for(int i=0; i<=(int)vec.size() && vec[i].submitted; i++){
			printf("%d %d %d\n", vec[i].num, vec[i].nsolved, vec[i].time);
		}
		if (N>0) printf("\n");
	}
	return 0;
}