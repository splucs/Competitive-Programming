#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

//O(n), retorna o LPS ímpar para cada posição, LPS=2*L+1
void manacher(char* str, int* L){
    int n = strlen(str), c = 0, r = 0;
    for(int i = 0; i < n; i++) {
        if(i < r && 2*c >= i) L[i] = min(L[2*c-i], r-i);
        else L[i] = 0;
        while(i-L[i]-1 >= 0 && i+L[i]+1 < n &&
            str[i-L[i]-1] == str[i+L[i]+1]) L[i]++;
        if(i+L[i]>r) { c=i; r=i+L[i]; }
    }
}

//longest palindromic substring
int LPS(char* text){
    int n=2*strlen(text)+1;
    char temp[n+1];
    for(int i=0, k=0; text[i]; i++) {
        temp[k++]='|'; temp[k++]=text[i];
    }
    temp[n-1]='|'; temp[n]='\0';
    int L[n], ans=1;
    manacher(temp, L);
    for(int i=0; i<n; i++)
        if (L[i] == i) ans = max(ans, L[i]);
    return ans;
}

char str[MAXN];

int main() {
	scanf("%s", str);
	printf("%d\n", LPS(str));
	return 0;
}