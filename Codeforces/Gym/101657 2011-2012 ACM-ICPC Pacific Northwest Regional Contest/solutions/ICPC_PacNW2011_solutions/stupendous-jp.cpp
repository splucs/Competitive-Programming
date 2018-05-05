#include<cstdio>
struct interval{int s, e;};
int n, m;
int a[30];
interval b[20];
inline bool intersect(interval &a, interval &b)
{
	return (a.s<b.s && b.s<a.e && a.e<b.e) || (b.s<a.s && a.s<b.e && b.e<a.e);
}
int main()
{
	int i, j, k;
	while(true)
	{
		scanf("%d", &n);
		if(!n) break;
		m=n*2;
		for(i=1;i<=m;i++) scanf("%d", &a[i]);
		bool flag=false;
		for(i=1;i<=m;i++)
		{
			for(j=i+1;j<=m && a[i]!=a[j];j++);
			if(j>m) continue;
			if((j-i)%2==0){flag=true; break;}
		}
		if(flag){printf("escaped\n"); continue;}
		for(i=1;i<=m;i++)
		{
			for(j=i+1;j<=m && a[i]!=a[j];j++);
			if(j>m) continue;
			for(k=1;i+k<j-k;k++){a[0]=a[i+k]; a[i+k]=a[j-k]; a[j-k]=a[0];}
		}
		for(i=1;i<=m;i++)
		{
			for(j=i+1;j<=m && a[i]!=a[j];j++);
			if(j>m) continue;
			b[a[i]-1].s=i; b[a[i]-1].e=j;
		}
		bool ans=false;
		for(int mask=0;mask<(1<<n);mask++)
		{
			if(mask==5)
				i=i;
			bool flag=false;
			for(i=0;i<n && !flag;i++)
			{
				for(j=i+1;j<n;j++)
				{
					if(((mask>>i)&1)==((mask>>j)&1) && intersect(b[i], b[j]))
					{
						flag=true; break;
					}
				}
			}
			if(!flag){ans=true; break;}
		}
		printf("%s\n", ans?"caught":"escaped");
	}
	return 0;
}
