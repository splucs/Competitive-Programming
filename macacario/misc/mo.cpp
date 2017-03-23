#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXA 1000009
#define MAXN 200009

int arr[MAXN], N, sqrtN, M;
typedef long long int ll;
ll inArray[MAXA];

struct query
{
	int l;
	int r;
	int id;
	ll result;
	query() { l=r=id=0; }
	query(int _id, int _l, int _r){
		id = _id; l = _l; r = _r;
	}
} queries[MAXN];

bool lrcomp(query a, query b){
	if (a.l/sqrtN != b.l/sqrtN) return a.l/sqrtN < b.l/sqrtN;
  	return a.r > b.r;
}

bool idcomp(query a, query b){
	return a.id < b.id;
}

int currentL;
int currentR;
ll currentAns;

void updateRight(query & q){
	ll cur;
	while(currentR < q.r){
		cur = arr[++currentR];
		currentAns += (2*inArray[cur]+1)*cur;
		inArray[cur]++;
	}
	while(currentR > q.r){
		cur = arr[currentR--];
		inArray[cur]--;
		currentAns -= (2*inArray[cur]+1)*cur;
	}
}

void updateLeft(query & q){
	ll cur;
	while(currentL < q.l){
		cur = arr[currentL++];
		inArray[cur]--;
		currentAns -= (2*inArray[cur]+1)*cur;
	}
	while(currentL > q.l){
		cur = arr[--currentL];
		currentAns += (2*inArray[cur]+1)*cur;
		inArray[cur]++;
	}
}

void solve(){

	sqrtN = sqrt(N);
	sort(queries, queries+M, &lrcomp);

	memset(&inArray, 0, sizeof inArray);

	currentL = 1;
	currentR = 0;
	currentAns = 0;

	for(int i=0; i<M; i++){
		if (queries[i].r > currentR){
			updateRight(queries[i]);
			updateLeft(queries[i]);
		}
		else{
			updateLeft(queries[i]);
			updateRight(queries[i]);
		}
		queries[i].result = currentAns;
	}

	sort(queries, queries+M, &idcomp);
}

int main()
{
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++){
		scanf("%d", arr+i);
	}
	int l, r;
	for(int i=0; i<M; i++){
		scanf("%d %d", &l, &r);
		queries[i] = query(i, l, r);		
	}
	solve();
	for(int i=0; i<M; i++){
		cout << queries[i].result << endl;		
	}
	return 0;
}