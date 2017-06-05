#include <cstdio>
#include <cstring>

int main()
{
	int L, x, y, z;
	char str[5];
	while(true){
		scanf(" %d", &L);
		if (L==0) break;
		x=1;
		y=z=0;
		for (int i=1; i<L; i++){
			scanf(" %s", str);
			if (!strcmp(str, "+y")){
				if (x==1){
					x=0; y=1;
				}
				else if (x==-1){
					x=0; y=-1;
				}
				else if (y==1){
					y=0; x=-1;
				}
				else if (y==-1){
					y=0; x=1;
				}
			}
			else if (!strcmp(str, "-y")){
				if (x==1){
					x=0; y=-1;
				}
				else if (x==-1){
					x=0; y=1;
				}
				else if (y==1){
					y=0; x=1;
				}
				else if (y==-1){
					y=0; x=-1;
				}
			}
			else if (!strcmp(str, "+z")){
				if (x==1){
					x=0; z=1;
				}
				else if (x==-1){
					x=0; z=-1;
				}
				else if (z==1){
					z=0; x=-1;
				}
				else if (z==-1){
					z=0; x=1;
				}
			}
			else if (!strcmp(str, "-z")){
				if (x==1){
					x=0; z=-1;
				}
				else if (x==-1){
					x=0; z=1;
				}
				else if (z==1){
					z=0; x=1;
				}
				else if (z==-1){
					z=0; x=-1;
				}
			}
		}
		if (x==1) printf("+x\n");
		if (x==-1) printf("-x\n");
		if (y==1) printf("+y\n");
		if (y==-1) printf("-y\n");
		if (z==1) printf("+z\n");
		if (z==-1) printf("-z\n");
	}
	return 0;
}