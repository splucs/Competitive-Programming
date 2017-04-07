#include <cstdio>
#include <map>
#include <iostream>
#include <string>
using namespace std;

string infixa, prefixa;
map<char, int> in, pre;

void post(int inmin, int inmax, int premin, int premax){
    if (inmin>inmax) return;
    char pivot = prefixa[premin];
    int inpos = in[pivot];
    int firstRight=premin+1;
    while(inpos>in[prefixa[firstRight]]){
        firstRight++;
    }
    post(inmin, inpos-1, premin+1, firstRight-1);
    post(inpos+1, inmax, firstRight, premax);
    printf("%c", pivot);
}

int main()
{
    int C, N;
    scanf("%d", &C);
    while(C-->0){
        scanf("%d", &N);
        cin >> prefixa >> infixa;
        for (int i = 0; i < N; ++i)
        {
            in[infixa[i]]=i;
            pre[prefixa[i]]=i;
        }
        post(0, N-1, 0, N-1);
        printf("\n");
        in.clear();
        pre.clear();
    }
    return 0;
}