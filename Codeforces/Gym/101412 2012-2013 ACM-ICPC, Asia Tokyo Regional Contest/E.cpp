#include <bits/stdc++.h>
using namespace std;
#define MAXN 51
#define INF 1000000009
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

int h,w;
char mp[51][51];

int movx[4] = {0,0,1,-1};
int movy[4] = {1,-1,0,0};

bool inBounds(int posx,int posy){
	int x[4] = {posx,posx,posx+1,posx+1};
	int y[4] = {posy,posy+1,posy+1,posy};

	for (int i=0;i<4;i++){
		if (x[i]<0||y[i]<0||x[i]>=h||y[i]>=w||mp[x[i]][y[i]]=='*')return false;
	}
	return true;
}

void setBlank(int x,int y,int dir,int sig,int &x1,int &y1,int &x2,int &y2){
	x1 = movx[dir]*sig+x, y1 = movy[dir]*sig+y;
	if (movx[dir]*sig==1)x1++;
	if (movy[dir]*sig==1)y1++;
	if (movx[dir]==0)x2 = x1+1, y2 = y1;
	if (movy[dir]==0)x2 = x1, y2 = y1+1;
}

void fixKing(int x,int y,char c){
	mp[x][y] = c;
	mp[x+1][y] = c;
	mp[x+1][y+1] = c;
	mp[x][y+1] = c;
}

int costToMove(int x1,int y1,int x2,int y2){
	queue<ii> inuse;
	int goal = x2*w+y2,dist,cur,x,y;
	bool vis[MAXN][MAXN] = {};

	inuse.push(ii(x1*w+y1,0));
	vis[x1][y1] = true;

	while (!inuse.empty()){
		dist = inuse.front().second;
		cur = inuse.front().first;
		inuse.pop();

		if (cur==goal)return dist;

		x1 = cur/w, y1 = cur%w;

		for (int i=0;i<4;i++){
			x = x1+movx[i];
			y = y1+movy[i];

			if (x<0||y<0||x>=h||y>=w||vis[x][y]||mp[x][y]=='*')continue;

			vis[x][y] = true;
			inuse.push(ii(x*w+y,dist+1));
		}
	}
	return INF;
}

int solve(int king,int b1,int b2){
	int kx,ky,b1x,b1y,b2x,b2y,dir,dist,x,y;
	int c1x,c1y,c2x,c2y,x1,y1,d1,d2,d3,d4,cost;

	kx = king/w, ky = king%w;

	int val[4][MAXN][MAXN];
	memset(val,-1,sizeof(val));
	priority_queue<iii> inuse;

	b1x = b1/w, b1y = b1%w, b2x = b2/w, b2y = b2%w;

	for (int i=0;i<4;i++){
		setBlank(kx,ky,i,-1,c1x,c1y,c2x,c2y);

		fixKing(kx,ky,'*');
        d1 = costToMove(b1x,b1y,c1x,c1y);
        d2 = costToMove(b1x,b1y,c2x,c2y);
        d3 = costToMove(b2x,b2y,c1x,c1y);
        d4 = costToMove(b2x,b2y,c2x,c2y);
        fixKing(kx,ky,'X');

		cost = min(d1+d4,d2+d3);

		if (cost>=INF)continue;

		inuse.push(iii(-cost,ii(king,i)));
		val[i][kx][ky] = cost;
	}

	while (!inuse.empty()){
		king = inuse.top().second.first;
		dir = inuse.top().second.second;
		dist = -inuse.top().first;
		inuse.pop();

        //cout<<"king, dir, dist: "<<king<<" "<<dir<<" "<<dist<<endl;

		if (king==0)return dist;

		kx = king/w, ky = king%w;

		if (dist>val[dir][kx][ky])continue;
		setBlank(kx,ky,dir,-1,b1x,b1y,b2x,b2y);

		for (int i=0;i<4;i++){
			x = movx[i]+kx;
			y = movy[i]+ky;

            //cout<<"x,y: "<<x<<" "<<y<<endl;

			if (!inBounds(x,y)||(val[i][x][y]>=0&&val[i][x][y]<dist))continue;

			setBlank(kx,ky,i,1,c1x,c1y,c2x,c2y);

            //cout<<"b1,b2,c1,c2: "<<b1x*w+b1y<<" "<<b2x*w+b2y<<" "<<c1x*w+c1y<<" "<<c2x*w+c2y<<endl;

			fixKing(kx,ky,'*');
			d1 = costToMove(b1x,b1y,c1x,c1y);
			d2 = costToMove(b1x,b1y,c2x,c2y);
			d3 = costToMove(b2x,b2y,c1x,c1y);
			d4 = costToMove(b2x,b2y,c2x,c2y);
            fixKing(kx,ky,'X');

			cost = dist+1+min(d1+d4,d2+d3);

            //cout<<"cost: "<<cost<<endl;

			if (cost>=INF)continue;

			if (val[i][x][y]<0||cost<val[i][x][y]){
				val[i][x][y] = cost;
				inuse.push(iii(-cost,ii(x*w+y,i)));
			}

		}
	}
	return -1;
}

int main(){
	int blank[2],k,king;
	while (scanf("%d%d",&h,&w)&&h!=0){
		k = 0;
		king = -1;
		for (int i=0;i<h;i++){
			scanf("%s",&mp[i]);
			for (int j=0;j<w;j++){
				if (mp[i][j]=='.')blank[k++] = i*w+j;
				else if (mp[i][j]=='X'&&king==-1)king = i*w+j;
			}
		}
		if (king==0)printf("0\n");
		else printf("%d\n",solve(king,blank[0],blank[1]));
	}
}