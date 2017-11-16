#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int year, volume, number, pagefrom, pageto, page;
char buffer[MAXN];
string author, title, journal, publisher;

bool hasend() {
	int len = strlen(buffer);
	for(int i=0; i<len; i++) {
		if (buffer[i] == '\"') {
			buffer[i] = 0;
			return true;
		}
	}
	return false;
}

void readAuthors() {
	scanf(" = \" ");
	bool end = false;
	list<string> names;
	while (!end) {
		list<string> name;
		string fullname;
		bool endname = false;
		while(!endname) {
			scanf(" %s ", buffer);
			//printf("%s ", buffer);
			if (hasend()) {
				end = true;
				endname = true;
			}
			if (strcmp(buffer, "and") == 0) {
				endname = true;
			}
			else name.push_back(string(buffer));
		}
		fullname = name.back();
		name.pop_back();
		while(!name.empty()) {
			fullname = fullname + " " + name.front()[0] + ".";
			name.pop_front();
		}
		names.push_back(fullname);
	}
	author = names.back();
	names.pop_back();
	while(!names.empty()) {
		author = author + ", " + names.back();
		names.pop_back();
	}
	printf("\nauthors read: |%s|\n", author.c_str());
}

void readTitle() {
	scanf(" = \" ");
	bool end = false;
	title = "";
	while(!end) {
		scanf(" %s ", buffer);
		if (hasend()) {
			end = true;
		}
		title = title + " " + buffer;
	}
}

void readJournal() {
	scanf(" = \" ");
	bool end = false;
	journal = "";
	while(!end) {
		scanf(" %s ", buffer);
		if (hasend()) {
			end = true;
		}
		journal = journal + " " + buffer;
	}
}

void readPublisher() {
	scanf(" = \" ");
	bool end = false;
	publisher = "";
	while(!end) {
		scanf(" %s ", buffer);
		if (hasend()) {
			end = true;
		}
		publisher = publisher + " " + buffer;
	}
}

void readVolume() {
	scanf(" = \" %d \" ", &volume);
}

void readYear() {
	scanf(" = \" %d \" ", &year);
}

void readNumber() {
	scanf(" = \" %d \" ", &number);
}

void readPages() {
	scanf(" = \" %s ", buffer);
	int len = strlen(buffer);
	bool single = true;
	for(int i=0; i<len && !single; i++) {
		if (buffer[i] == '-') single = false;
	}
	if (single) sscanf(buffer, "%d \" ", &page);
	else sscanf(buffer, "%d--%d \" ", &pagefrom, &pageto);
}

void readBlock() {
	scanf(" { ");
	author = title = journal = publisher = "";
	year = page = pagefrom = pageto = volume = number = -1;
	while(true) {
		scanf(" %s", buffer);
		if (strcmp(buffer, "}") == 0) break;
		else if (strcmp(buffer, "author") == 0) readAuthors();
		else if (strcmp(buffer, "title") == 0) readTitle();
		else if (strcmp(buffer, "journal") == 0) readJournal();
		else if (strcmp(buffer, "publisher") == 0) readPublisher();
		else if (strcmp(buffer, "year") == 0) readYear();
		else if (strcmp(buffer, "volume") == 0) readVolume();
		else if (strcmp(buffer, "number") == 0) readNumber();
		else if (strcmp(buffer, "pages") == 0) readPages();
	}
}

int cnt = 1;

void printBook() {
	readBlock();
	printf("[%d] %s %s", cnt++, author.c_str(), title.c_str());
	if (volume >= 0) printf(", Vol. %d", volume);
	printf(" -- %s, %d", publisher, year);
	printf("\n");
}

void printArticle() {
	readBlock();
	printf("[%d] %s %s // %s", cnt++, author.c_str(), title.c_str(), journal.c_str());
	if (volume >= 0) printf(", %d", volume);
	if (number >= 0) printf(" (%d)", number);
	printf(" -- %d", year);
	if (page >= 0) printf(" -- p. %d", page);
	if (pagefrom >= 0 && pageto >= 0) printf(" -- pp. %d--%d", pagefrom, pageto);
	printf("\n");
}

int main() {
	//freopen("bibtex.in", "r", stdin);
	//freopen("bibtex.out", "w", stdout);
	
	while(!feof(stdin)) {
		scanf(" %s ", buffer);
		if (strcmp(buffer, "@book") == 0) printBook();
		else printArticle();
	}
		
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}