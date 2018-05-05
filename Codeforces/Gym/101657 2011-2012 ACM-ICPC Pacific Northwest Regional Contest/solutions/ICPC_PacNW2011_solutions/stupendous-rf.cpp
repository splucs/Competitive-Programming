/*************************************************************************
 Solution to "Stupendous Man" by Ralph Furmaniak (problem author)
 2011 Pacific Northwest Regional Programming Contest
 
 Sketch of solution idea is as follows:
 
     For each crossing, replace the crossing X with two strands just
     touching but not crossing )(, so that you still get a single loop.
     This is equivalent to finding the two occurrences of each number and
     reversing the sequence in between.  So if you start with 1,2,3,1,2,3
     you end with 1,3,2,1,2,3.  The problem is now can you find a non-
     intersecting loop that touches itself at these N points.  From the
     sequence 1,3,2,1,2,3 try to connect the pairs either above or below:
      _____
     |     |
     1,3,2,1,2,3
       | |___| |
       |_______|
     
     The loop exists if and only if you can do this (proof left to the
     reader, or look up Read & Rosenstiehl 1976 if reader is lazy).
 
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(void) {
	int N;
	while((cin>>N) && N) {
		vector<int> code(2*N);
		bool doable = true;
		for(int i=0; i<2*N; i++) cin >> code[i];
		for(int i=0; i<2*N; i++) for(int j=i+1; j<2*N; j++)
			if(code[i]==code[j] && (i%2==j%2)) doable=false;
		if(!doable) {
			cout << "escaped" << endl;
			continue;
		}
		doable = false;
		vector<vector<int> > where(N+1);
		for(int i=0; i<2*N; i++) for(int j=i+1; j<2*N; j++) if(code[i]==code[j])
			reverse(&code[i+1], &code[j]);
		for(int i=0; i<2*N; i++) where[code[i]].push_back(i);
		for(int msk=0; msk<(1<<N+1); msk+=2) {
			bool isthisonegood=true;
			for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
				if(where[i][0]<where[j][0] && where[j][0]<where[i][1] && where[i][1]<where[j][1])
					if((msk>>i)%2 == (msk>>j)%2)
						isthisonegood = false;
			if(isthisonegood) doable=true;
		}
		cout << (doable ? "caught" : "escaped") << endl;
	}
    return 0;
}
