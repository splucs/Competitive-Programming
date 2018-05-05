#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

bool bissexto(int year) {
	if (year%400 == 0) return true;
	if (year%100 == 0) return false;
	if (year%4 == 0) return true;
	return false;
}

int days_to_ini(int y, int m, int d, int mm) {
	if (mm == m) return d;
	if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) return 31 + days_to_ini(y,m,d,mm+1);
	if (mm == 2) return 28 + days_to_ini(y,m,d,mm+1);
	return 30 + days_to_ini(y,m,d,mm+1);	
}

int p_29[3000][7], before_29[3000][7], after_29[3000][7];

void precompute() {
	int b29 = 0, a29 = 0, acum29 = 423;
	for (int i = 0; i < 3000; i++) {
		for (int j = 0; i > 0 && j < 7; j++) {
			p_29[i][j]      = p_29[i-1][j];
			before_29[i][j] = before_29[i-1][j];
			after_29[i][j]  = after_29[i-1][j];
		}
		before_29[i][b29%7]++;
		after_29[i][a29%7]++;
		if (bissexto(i+1583)) p_29[i][acum29%7]++;   // Checar isso aqui depois

		if (bissexto(i+1583)) {
			b29 += 2;
		} else b29 += 1;
		
		if (bissexto(1+i+1583)) {
			a29 += 2;
			acum29 += 2;
		} else {
			a29 += 1;
			acum29 += 1;
		}
	}
}

void compute_after(int* c, int year) {
	for (int i = 0; i < 7; i++) c[i] = 0;
	
	if (year < 1583) {
		return;
	}
	
	year -= 1583;
	int t = year/2800;
	
	//printf("%d %d\n", year, t);
	for (int i = 0; i < 7; i++) c[i] += t*after_29[2800-1][i];
	for (int i = 0; i < 7; i++) c[i] += after_29[year - t*2800][i];
	return;
}


void compute_before(int* c, int year) {
	for (int i = 0; i < 7; i++) c[i] = 0;
	
	if (year < 1583) {
		return;
	}
	
	year -= 1583;
	int t = year/2800;
	for (int i = 0; i < 7; i++) c[i] += t*before_29[2800-1][i];
	for (int i = 0; i < 7; i++) c[i] += before_29[year - t*2800][i];
	
	return;
}

void compute_bissexto(int* c, int year) {
	for (int i = 0; i < 7; i++) c[i] = 0;
	
	if (year < 1583) {
		return;
	}
	
	year -= 1583;
	int t = year/2800;
	for (int i = 0; i < 7; i++) c[i] += t*p_29[2800-1][i];
	for (int i = 0; i < 7; i++) c[i] += p_29[year - t*2800][i];
	
	return;
}
int main() {
	int Q, y1, y2, m, d, shift;
	precompute();
	
	scanf("%d", &Q);
	
	while(Q--) {
		scanf("%d %d %d %d", &y1, &y2, &m, &d);
		int a[7], b[7];
		
		// Caso bissexto
		if (m == 2 && d == 29) {
			shift = 0;
			
			compute_bissexto(a, y1-1);
			compute_bissexto(b, y2);		
		} else if (m >= 3) { // Caso after 29
			shift = days_to_ini(y1, m, d, 1);
			
			compute_after(a, y1-1);
			compute_after(b, y2);		
		} else { // Caso before 29
			shift = days_to_ini(y1, m, d, 1);

			compute_before(a, y1-1);
			compute_before(b, y2);	
		}
		for (int i = 0; i < 7; i++) {
			if (i > 0) printf(" ");
			printf("%d", b[(2+i+700 - shift)%7] - a[(2+i+700 - shift)%7]);
		}
		printf("\n");
	}
}