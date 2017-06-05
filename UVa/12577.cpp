#include <cstdio>
#include <cstring>

int main()
{
	char str[10], caseNo=0;
	while (true){
		caseNo++;
		scanf(" %s", str);
		if (!strcmp(str, "*")) break;
		else if (!strcmp(str, "Hajj")) printf("Case %d: Hajj-e-Akbar\n", caseNo);
		else printf("Case %d: Hajj-e-Asghar\n", caseNo);
	}
	return 0;
}