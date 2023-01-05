#include <cstdio>
#include <map>
#include <stack>
#include <cstring>
using namespace std;
int main()
{
    int N, len;
    map<char, int> precedence;
    precedence['+']=1;
    precedence['-']=1;
    precedence['*']=2;
    precedence['/']=2;
    precedence['^']=3;
    char polish[400];
    scanf("%d", &N);
    for (int j=0; j<N; j++){
        scanf(" %s", polish);
        len=strlen(polish);
        stack<char> pilha;
        for (int i=0; i<len; i++){
            if (polish[i]=='+' || polish[i]=='-' || polish[i]=='*' || polish[i]=='/' || polish[i]=='^'){
                while (!pilha.empty() && pilha.top()!='(' && precedence[pilha.top()]>=precedence[polish[i]]){
                    printf("%c", pilha.top());
                    pilha.pop();
                }
                pilha.push(polish[i]);
            }
            else if (polish[i]=='(') pilha.push('(');
            else if (polish[i]==')'){
                while (pilha.top()!='('){
                    printf("%c", pilha.top());
                    pilha.pop();
                }
                pilha.pop();
            }
            else if ((polish[i]>='a' && polish[i]<='z') || (polish[i]>='A' && polish[i]<='Z') || (polish[i]>='0' && polish[i]<='9'))printf("%c", polish[i]);
        }
        while (!pilha.empty()){
            printf("%c", pilha.top());
            pilha.pop();
        }
        printf("\n");
    }
    return 0;
}
