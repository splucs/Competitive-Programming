#include <cstdio>
#include <set>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <bitset>
using namespace std;

map<int, int> dist;

inline int arr2mask(int * arr){
	int ans = 0;
	for(int i=0; i<8; i++){
		ans <<= 3;
		ans |= arr[i];
	}
	return ans;
}

inline void mask2arr(int mask, int * arr){
	for(int i=7; i>=0; i--){
		arr[i] = mask & 7;
		mask >>= 3;
	}
}

int main(){
	int arr[8], vet[8], aux[8], inv[1009], distu, distv, s, t, u, v, w;
	for(int i=0; i<8; i++){
		scanf("%d", vet+i);
		for(int j=0; j<=i; j++){
			if (vet[i] == vet[j]){
				arr[i] = j;
				break;
			}
		}
		inv[vet[i]] = arr[i];
	}
	s = arr2mask(arr);		
	for(int i=0; i<8; i++){
		scanf("%d", aux+i);
		arr[i] = inv[aux[i]];
	}
	t = arr2mask(arr);
	dist[s] = 0;
	set<pair<int, int> > q;
	q.insert(make_pair(dist[s], s));
	while(!q.empty())
	{
		u = q.begin()->second;
		distu = q.begin()->first;
		if (u == t) break;
		q.erase(q.begin());
		mask2arr(u, arr);
		for(int i=0; i<8; i++){
			if (i<7 && i!=3){
				w = vet[arr[i]] + vet[arr[i+1]];
				swap(arr[i], arr[i+1]);
				v = arr2mask(arr);
				swap(arr[i], arr[i+1]);
				if (!dist.count(v) || (distv=dist[v]) > distu + w){
					if(dist.count(v)) q.erase(make_pair(distv, v));
					distv=dist[v] = distu+w;
					q.insert(make_pair(distv, v));
				}				
			}
			if (i<4){
				w = vet[arr[i]] + vet[arr[i+4]];
				swap(arr[i], arr[i+4]);
				v = arr2mask(arr);
				swap(arr[i], arr[i+4]);
				if (!dist.count(v) || (distv=dist[v]) > distu + w){
					if(dist.count(v)) q.erase(make_pair(distv, v));
					distv=dist[v] = distu+w;
					q.insert(make_pair(distv, v));
				}				
			}
		}
	}
	
	printf("%d\n", dist[t]);
	return 0;
}
