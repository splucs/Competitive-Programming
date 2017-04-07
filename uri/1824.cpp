#include <cstdio>

bool used[1000][1000];
int mp[1000][1000];

int main(){
int m,n,x,y,cnt,maxx,aux,t=1;
while(scanf("%d%d",&m,&n)&&(m!=0||n!=0)){
    for (int i=0;i<m;i++)
        for (int j=0;j<n;j++){
                scanf("%d",&mp[i][j]);
        used[i][j]=false;
        }
    x=y=0,cnt=0,used[0][0]=true,maxx=m*n;
    while(cnt!=maxx){
    cnt++;
        aux=mp[x][y];
        y=aux>=2&&aux<=4?y+1:aux>=6&&aux<=8?y-1:y;
        x = aux>=4&&aux<=6?x+1:aux==7||aux==3?x:x-1;
        if (x>=0&&x<m&&y>=0&&y<n){
            if (!used[x][y]){
                used[x][y]=true;
            }else break;
        }else break;
    }
    printf("Instancia %d\n",t++);
    if (cnt==maxx)printf("sim\n\n");
    else printf("nao\n\n");
}
}