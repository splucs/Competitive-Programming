#include <cstdio>

char seq[26];

void move(int i){
char u = seq[i];
for (;i>0;i--)seq[i]=seq[i-1];
seq[i]=u;
}

int main(){
int m,p,encoded,inst=1;
char ans[10010];
while(scanf("%d",&m)&&m!=0){
        p=0;
for (int i=0;i<26;i++)seq[i]='A'+i;
    for (int i=0;i<m;i++){
            scanf("%d",&encoded);
    ans[p++]=seq[encoded-1];
    move(encoded-1);
    }
    ans[p]=0;
    printf("Instancia %d\n%s\n\n",inst++,ans);
}
}
