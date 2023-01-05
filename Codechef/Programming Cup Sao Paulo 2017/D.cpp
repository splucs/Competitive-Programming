#include <bits/stdc++.h>
using namespace std;

int N, C, M;

class UnionFind {

private:

	vector<int> parent, rank;

public:

	UnionFind(int N) {

		rank.assign(N+9, 0);

		parent.assign(N+9, 0);

		for (int i = 0; i < N; i++) parent[i] = i;

	}

	int find(int i) {

		while(i != parent[i]) i = parent[i];

		return i;

	}

	bool isSameSet(int i, int j) {

		return find(i) == find(j);

	}

	void unionSet (int i, int j) {

		if (isSameSet(i, j)) return;

		int x = find(i), y = find(j);

		if (rank[x] > rank[y]) parent[y] = x;

		else {

			parent[x] = y;

			if (rank[x] == rank[y]) rank[y]++;

		}

	}

};

typedef pair<int, int> ii;
typedef long long ll;
vector< pair<ll, ii> > edgeList; // (weight, two vertices) of the edge

ll kruskal(){

	ll cost = 0;

	UnionFind UF(N);

	pair<int, ii> edge;

	sort(edgeList.begin(), edgeList.end());

	for (int i = 0; i < C; i++) {

		edge = edgeList[i];

		if (!UF.isSameSet(edge.second.first, edge.second.second)) { 
			cost += edge.first;
			UF.unionSet(edge.second.first, edge.second.second);
		}

	}

	return cost;

}

int main(){
	
	int a, b, c;
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin>>N>>C;
	N++;
	for (int i = 0; i < C; i++){
		cin>>a>>b>>c;
		edgeList.push_back(make_pair(c,ii(a, b)));
	}
	cout<<kruskal()<<endl;
}