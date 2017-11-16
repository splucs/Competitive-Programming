#include <cstdio>

int main(){
	char c;
	int lastman = 0;
	int i=1;
	while(scanf(" %c", &c)!=EOF){
		if (c == 'M'){
			lastman = i;
		}
		if (c != 'M' && c != 'F') continue;
		i++;
	}
	if (lastman == 0) lastman++;
	printf("%d\n", i - lastman);
	bool hasprinted = false;
	for(int j = lastman; j<i; j++){
		if (hasprinted) printf(" ");
		hasprinted = true;
		printf("%d", j);
	}
	if (i > lastman) printf("\n");
	return 0;
}