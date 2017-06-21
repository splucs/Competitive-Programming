#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main()
{
    string s;
    int balance;
    bool correct;
    while (true){
        getline(cin, s);
        if(!cin) break;
        correct = true;
        balance = 0;
        for (int i=0; i<s.size() && correct; i++){
            if (s[i]=='(') balance++;
            else if (s[i]==')' && balance>0) balance--;
            else if (s[i]==')') correct = false;
        }
        if (balance!=0) correct = false;
        if (correct) printf("correct\n");
        else printf("incorrect\n");
    }
    return 0;
}
