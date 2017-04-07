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
    while(cin >> prefixa >> infixa){
        for (int i = 0; i < prefixa.size(); ++i)
        {
            in[infixa[i]]=i;
            pre[prefixa[i]]=i;
        }
        post(0, prefixa.size()-1, 0, prefixa.size()-1);
        printf("\n");
        in.clear();
        pre.clear();
    }
    return 0;
}