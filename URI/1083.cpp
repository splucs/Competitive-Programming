#include <cstdio>
#include <map>
#include <stack>
#include <cstring>
using namespace std;
bool isOp(char a)
{
    if (a=='+' || a=='-' || a=='*' || a=='/' || a=='^' || a=='>' || a=='<' || a=='=' || a=='#' || a=='.' || a=='|') return true;
    else return false;
}
bool isCa(char a)
{
    if ((a>='a' && a<='z') || (a>='A' && a<='Z') || (a>='0' && a<='9')) return true;
    else return false;
}
void add(char* bizarro, char a)
{
    int len = strlen(bizarro);
    bizarro[len]=a;
    bizarro[len+1]='\0';
}
int main()
{
    int len;
    map<char, int> precedence;
    precedence['|']=1;
    precedence['.']=2;
    precedence['>']=precedence['<']=precedence['=']=precedence['#']=3;
    precedence['+']=precedence['-']=4;
    precedence['*']=precedence['/']=5;
    precedence['^']=6;
    char polish[4000], bizarro[4000];
    while(scanf("%s", polish)!=EOF){
        len=strlen(polish);
        stack<char> pilha;
        bool lex=false, syn=false;
        strcpy(bizarro, "");
        for (int i=0; i<len && !lex; i++){
            if (isOp(polish[i])){
                if (i+1==len || i==0) syn=true;
                else if (!isCa(polish[i-1]) && polish[i-1]!=')') syn=true;
                else if (!isCa(polish[i+1]) && polish[i+1]!='(') syn=true;
                while (!pilha.empty() && pilha.top()!='(' && precedence[pilha.top()]>=precedence[polish[i]]){
                    add(bizarro, pilha.top());
                    pilha.pop();
                }
                pilha.push(polish[i]);
            }
            else if (polish[i]=='('){
                if(i>0 && (isCa(polish[i-1])) || polish[i-1]==')') syn = true;
                pilha.push('(');
            }
            else if (polish[i]==')'){
                if (i>0 && polish[i-1]=='(') syn=true;
                if (pilha.empty()){
                    syn = true;
                }
                while (!pilha.empty() && pilha.top()!='('){
                    add(bizarro, pilha.top());
                    pilha.pop();
                    if (pilha.empty()){
                        syn = true;
                        break;
                    }
                }
                if (!pilha.empty()) pilha.pop();
            }
            else if ((polish[i]>='a' && polish[i]<='z') || (polish[i]>='A' && polish[i]<='Z')){
                if (i==0) add(bizarro, polish[i]);
                else if (isOp(polish[i-1]) || polish[i-1]=='(') add(bizarro, polish[i]);
                else syn=true;
            }
            else if (polish[i]>='0' && polish[i]<='9'){
                if (i==0) add(bizarro, polish[i]);
                else if (isOp(polish[i-1]) || polish[i-1]=='(' || (polish[i-1]>='0' && polish[i-1]<='9')) add(bizarro, polish[i]);
                else syn=true;
            }
            else lex=true;
        }
        while (!lex && !syn && !pilha.empty()){
            if (pilha.top()=='('){
                syn=true;
                break;
            }
            add(bizarro, pilha.top());
            pilha.pop();
        }
        if (lex) printf("Lexical Error!\n");
        else if (syn) printf("Syntax Error!\n");
        else printf("%s\n", bizarro);
    }
    return 0;
}

