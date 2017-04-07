#include <cstdio>

struct node{
	int left, right, father;
	int product, start, end;
};

int vet[100009], pos[100009], N, K, treesize;
node nodes[250009];

int build(int a, int b, int father){
	int no = treesize++;
	nodes[no].father = father;
	nodes[no].start = a;
	nodes[no].end = b;
	if(a==b){
		nodes[no].product = vet[a];
		nodes[no].left = nodes[no].right = -1;
		pos[a]=no;
	}
	else{
		nodes[no].left = build(a,(a+b)/2,no);
		nodes[no].right = build(((a+b)/2)+1,b,no);
		nodes[no].product = nodes[nodes[no].left].product*nodes[nodes[no].right].product;
	}
	return no;
}

void update(int no, int product){
	nodes[no].product = product;
	if(nodes[no].father==-1) return;
	else if(no==nodes[nodes[no].father].left)
		update(nodes[no].father, product*nodes[nodes[nodes[no].father].right].product);
	else update(nodes[no].father, product*nodes[nodes[nodes[no].father].left].product);
}

int query(int a, int b, int no){
	if(a==nodes[no].start && b==nodes[no].end) return nodes[no].product;
	int med = (nodes[no].start + nodes[no].end)/2;
	if(b<=med) return query(a,b,nodes[no].left);
	else if(a>med) return query(a,b,nodes[no].right);
	else return query(a,med,nodes[no].left)*query(med+1,b,nodes[no].right);
}

int main()
{
	char command;
	int I, J;
	while(scanf("%d %d", &N, &K)!=EOF){
		for(int i=0; i<N; i++){
			scanf("%d", vet+i);
			if(vet[i]>0) vet[i]=1;
			if(vet[i]<0) vet[i]=-1;
		}
		treesize = 0;
		build(0,N-1,-1);
		for(int i=0; i<K; i++){
			scanf(" %c %d %d", &command, &I, &J);
			if(command=='C') {
				if(J>0) J=1;
				if(J<0) J=-1;
				update(pos[I-1],J);
			}
			else if (command=='P'){
				I = query(I-1,J-1,0);
				if(I>0) printf("+");
				else if (I<0) printf("-");
				else printf("0");
			}
		}
		printf("\n");
	}
	return 0;
}