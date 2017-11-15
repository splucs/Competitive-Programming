#include <bits/stdc++.h>
using namespace std;

int getId(char* s){
	if (0 == strcmp(s, "pedra")) return 0;
	else if (0 == strcmp(s, "papel")) return 1;
	else return 2;
}

int main() {
	char s1[20], s2[20], s3[20];
	int c1, c2, c3;
	while(scanf(" %s %s %s", s1, s2, s3) != EOF) {
		c1 = getId(s1);
		c2 = getId(s2);
		c3 = getId(s3);
		if (c1 != c2 && c2 != c3 && c3 != c1){
			printf("Putz vei, o Leo ta demorando muito pra jogar...\n");
		}
		else if (c1 == c2){
			if ((c1+1)%3 == c3) printf("Urano perdeu algo muito precioso...\n");
			else printf("Putz vei, o Leo ta demorando muito pra jogar...\n");
		}
		else if (c2 == c3){
			if ((c2+1)%3 == c1) printf("Os atributos dos monstros vao ser inteligencia, sabedoria...\n");
			else printf("Putz vei, o Leo ta demorando muito pra jogar...\n");
		}
		else if (c3 == c1){
			if ((c3+1)%3 == c2) printf("Iron Maiden\'s gonna get you, no matter how far!\n");
			else printf("Putz vei, o Leo ta demorando muito pra jogar...\n");
		}
	}
	return 0;
}