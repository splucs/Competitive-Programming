#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

struct proposal{
	int requirementsMet;
	double price;
	string name;
};

bool operator <(proposal a, proposal b){
	if (a.requirementsMet < b.requirementsMet) return true;
	if (a.requirementsMet > b.requirementsMet) return false;
	if (a.price > b.price) return true;
	return false;
}

int main()
{
	int n, p, r, caseNo=1;
	proposal max, current;
	string str;
	while(true){
		scanf(" %d %d\n", &n, &p);
		if (n==0 && p==0) break;
		max.requirementsMet=-1;
		for(int i=0; i<n; i++){
			getline(cin, str);
		}
		for(int i=0; i<p; i++){
			getline(cin, current.name);
			scanf(" %lf %d\n", &current.price, &r);
			current.requirementsMet=r;
			for(int j=0; j<r; j++){
				getline(cin, str);
			}
			if (max<current) max=current;
		}
		if (caseNo>1) cout << endl;
		cout << "RFP #" << caseNo++ << endl <<  max.name << endl;
	}
	return 0;
}