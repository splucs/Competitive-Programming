#include <stdio.h>

int main(){
	int n, c, s;
	
	scanf("%d%d%d", &n, &c, &s);
	
	int pos=0;
	int count=0;
	if(s==1){
		count++;
	}
	for(int i=0; i<c; i++){
		int comm;
		scanf("%d", &comm);
		
		if(comm==1){
			//pos++;
			pos = (pos+1)%n;
		}
		else{
			//pos--;
			pos = (pos-1+n)%n;
		}
		
		if(pos==s-1){
			count++;
		}
	}
	
	printf("%d\n", count);

	return 0;
}

