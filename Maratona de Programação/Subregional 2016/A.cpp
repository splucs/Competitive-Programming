#include <cstdio>

int a[3];

bool recurs(int index,int qtt,int value){
	if (index==3){
		if (qtt>0&&value==0)return true;
		return false;
	}
	bool ret = recurs(index+1,qtt,value);
	ret|=recurs(index+1,qtt+1,value+a[index]);
	ret|=recurs(index+1,qtt+1,value-a[index]);
	return ret;
}

int main(){
	
	scanf("%d%d%d",&a[0],&a[1],&a[2]);
	if (recurs(0,0,0)){
		printf("S\n");
	}else{
		printf("N\n");
	}
	return 0;
}
