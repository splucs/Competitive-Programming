//Fast BIRL Transform
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define EPS 0.0000000000001
typedef pair<double,int> ii;

ii trackA[100000],trackB[100000];
int a[17],b[17],idx,idxA,idxB;

void recurs(int* A,int index,double val,int acum,ii *B){
    if (index<0){
        B[idx++]=ii(val,acum);
        return;
    }
    recurs(A,index-1,(double)val+log((double)A[index]),acum+(1<<index),B);
    recurs(A,index-1,val,acum,B);
}

bool sorte(ii a,ii b){
    return a.first<b.first;
}

int main(){
    int n,m,i,j,qtdA,qtdB;
    queue<int> ansA,ansB;
    scanf("%d%d",&n,&m);
    for (i=0;i<n;i++)scanf("%d",&a[i]);
    for (i=0;i<m;i++)scanf("%d",&b[i]);
    idx=0;
    recurs(a,n-1,0,0,trackA);
    idxA=idx;
    idx=0;
    recurs(b,m-1,0,0,trackB);
    idxB=idx;
    sort(trackA,trackA+idxA,sorte);
    sort(trackB,trackB+idxB,sorte);
    i=j=1;
    //for (i=0;i<idxB;i++)printf("%lf\n",trackB[i].first);
    //scanf("%d",&idx);
    //printf("%d %d\n",idxA,idxB);
    while(i<idxA&&j<idxB){
            //printf("%d %d,%lf %lf\n",i,j,trackA[i].first,trackB[j].first);
        if (abs(trackA[i].first-trackB[j].first)<EPS){
            break;
        }else if (trackA[i].first<trackB[j].first)i++;
        else j++;
    }
    if (i==idxA||j==idxB)printf("N\n");
    else{
        printf("Y\n");
        qtdA=qtdB=0;
        int u =  trackA[i].second;
        int v = trackB[j].second;
        i=0;
        //printf("%d %d\n",u,v);
        while (u>0){
            if (u%2==1){
                qtdA++;
                ansA.push(a[i]);
            }u/=2;
            i++;
        }i=0;
        while (v>0){
            if (v%2==1){
                qtdB++;
                ansB.push(b[i]);
            }v/=2;
            i++;
        }printf("%d %d\n%d",qtdA,qtdB,ansA.front());
        ansA.pop();
        while(!ansA.empty()){
            printf(" %d",ansA.front());
            ansA.pop();
        }printf("\n%d",ansB.front());
        ansB.pop();
        while(!ansB.empty()){
            printf(" %d",ansB.front());
            ansB.pop();
        }printf("\n");
    }
}