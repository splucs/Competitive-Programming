#include <cstdio>

int main()
{
	int months, n, ans, m;
	double debt, car, downpay, monthlypay, interest[109], perc;
	bool paid;
	while(true){
		scanf("%d %lf %lf %d", &months, &downpay, &car, &n);
		if (months<0) break;
		debt = car;
		monthlypay = debt/(double)months;
		car+=downpay;
		debt+=monthlypay;
		paid = false;
		ans=-1;
		for(int i=0; i<=months; i++){
			interest[i]=-1;
		}
		for(int i=0; i<n; i++){
			scanf("%d %lf", &m, &perc);
			interest[m]=perc;
		}
		for(int i=1; i<=months; i++){
			if (interest[i]==-1) interest[i]=interest[i-1];
		}
		for(int i=0; i<=months && ans==-1; i++){
			debt-=monthlypay;
			car*=(1.0-interest[i]);
			if (car>debt) ans=i;
		}
		if(ans==1) printf("1 month\n");
		else printf("%d months\n", ans);
	}
	return 0;
}