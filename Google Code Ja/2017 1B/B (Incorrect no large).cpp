#include <bits/stdc++.h>
using namespace std;

int T, N, R, O, Y, G, B, V, caseNo;
	
bool specialcase(){
	if (G == R && G > 0){
		printf("Case #%d: ", caseNo);
		if (G + R == N){
			for(int i=0; i<R; i++) printf("RG");
			printf("\n");
		}
		else printf("IMPOSSIBLE\n");
		return true;
	}
	if (G > R){
		printf("Case #%d: IMPOSSIBLE\n", caseNo);
		return true;
	}
	if (Y == V && Y > 0){
		printf("Case #%d: ", caseNo);
		if (V + Y == N){
			for(int i=0; i<Y; i++) printf("YV");
			printf("\n");
		}
		else printf("IMPOSSIBLE\n");
		return true;
	}
	if (V > Y){
		printf("Case #%d: IMPOSSIBLE\n", caseNo);
		return true;
	}
	if (O == B && O > 0){
		printf("Case #%d: ", caseNo);
		if (O + B == N){
			for(int i=0; i<B; i++) printf("OB");
			printf("\n");
		}
		else printf("IMPOSSIBLE\n");
		return true;
	}
	if (O > B){
		printf("Case #%d: IMPOSSIBLE\n", caseNo);
		return true;
	}
	return false;
}

char lastprinted;

void printred(){
	if (G > 0){
		printf("RGR");
		G--;
	}
	else printf("R");
	R--;
	lastprinted = 'r';
}

void printyellow(){
	if (V > 0){
		printf("YVY");
		V--;
	}
	else printf("Y");
	Y--;
	lastprinted = 'y';
}

void printblue(){
	if (O > 0){
		printf("BOB");
		O--;
	}
	else printf("B");
	B--;
	lastprinted = 'b';
}

int main()
{
	scanf("%d", &T);
	for(caseNo = 1; caseNo <= T; caseNo++){
		scanf("%d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);
		if (specialcase()) continue;
		R -= G;
		Y -= V;
		B -= O;
		if (R > Y+B || Y > R+B || B > R+Y) {
			printf("Case #%d: IMPOSSIBLE\n", caseNo);
			continue;
		}
		lastprinted = 'a';
		printf("Case #%d: ", caseNo);
		if (R >= Y && R >= B){
			while (R > 0){
				printred();
				if (Y > B) printyellow();
				else printblue();
			}
			if (B > Y) printblue();
			if (B < Y) printyellow();
			while(B > 0){
				bool first = (lastprinted != 'b');
				if (first) printblue();
				printyellow();
				if (!first) printblue();
			}
		}
		else if (B >= R && B >= Y){
			while (B > 0){
				printblue();
				if (R > Y) printred();
				else printyellow();
			}
			if (R > Y) printred();
			if (R < Y) printyellow();
			while(R > 0){
				bool first = (lastprinted != 'r');
				if (first) printred();
				printyellow();
				if (!first) printred();
			}
		}
		else if (Y >= R && Y >= B){
			while (Y > 0){
				printyellow();
				if (R > B) printred();
				else printblue();
			}
			if (R > B) printred();
			if (R < B) printblue();
			while(R > 0){
				bool first = (lastprinted != 'r');
				if (first) printred();
				printblue();
				if (!first) printred();
			}
		}
		printf("\n");
	}
	return 0;
}