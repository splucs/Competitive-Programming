#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main()
{
    string phrase;
    int found;
    char letter, aux;
    bool isTauto;
    while(true){
        getline(cin, phrase);
        if (phrase.compare("*")==0) break;
        found = 0;
        letter = phrase[0];
        if (letter>='A' && letter<='Z') letter += 'a'-'A';
        isTauto = true;
        while(isTauto){
        	found = phrase.find(' ', found+1);
        	if (found==std::string::npos || found+1==phrase.size()) break;
        	aux = phrase[found+1];
        	if (aux>='A' && aux<='Z') aux += 'a'-'A';
        	isTauto = (letter==aux);
        }
        if (isTauto) cout << "Y" << endl;
        else cout << "N" << endl;
    }
    return 0;
}
