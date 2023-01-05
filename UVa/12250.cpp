#include <cstdio>
#include <cstring>

int main()
{
	char str[1009];
	int caseNo=0;
	while (true){
		caseNo++;
		scanf(" %s", str);
		if (!strcmp(str, "HELLO")){
			printf("Case %d: ENGLISH\n", caseNo);
		}
		else if (!strcmp(str, "HOLA")){
			printf("Case %d: SPANISH\n", caseNo);
		}
		else if (!strcmp(str, "HALLO")){
			printf("Case %d: GERMAN\n", caseNo);
		}
		else if (!strcmp(str, "BONJOUR")){
			printf("Case %d: FRENCH\n", caseNo);
		}
		else if (!strcmp(str, "CIAO")){
			printf("Case %d: ITALIAN\n", caseNo);
		}
		else if (!strcmp(str, "ZDRAVSTVUJTE")){
			printf("Case %d: RUSSIAN\n", caseNo);
		}
		else if (!strcmp(str, "#")) break;
		else printf("Case %d: UNKNOWN\n", caseNo);
	}
	return 0;
}