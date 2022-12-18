#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXM 1009

map<string, int> nodes;
string name[MAXM];
vector<int> g[MAXM];
int par[MAXM], size[MAXM];
int nodeCount = 0;

char pwd[MAXM];

int getNode(string s) {
    if (!nodes.count(s)) {
        int u = nodeCount++;
        name[u] = s;
        nodes[s] = u;
    }
    return nodes[s];
}

string toString(const char * s) {
    return string(s, s+strlen(s));
}

void processCmd();

void processLs() {
    char sizeStr[MAXN], path[MAXN], fullPath[MAXM];
    int u = getNode(toString(pwd));
    g[u].clear();
    while(scanf(" %s", sizeStr)!=EOF) {
        if (!strcmp(sizeStr, "$")) {
            processCmd();
            return;
        }

        scanf(" %s", path);
        strcpy(fullPath, pwd);
        strcat(fullPath, path);
        if (!strcmp(sizeStr, "dir")) {
            strcat(fullPath, "/");
        }

        int v = getNode(toString(fullPath));
        g[u].push_back(v);
        par[v] = u;
        if (strcmp(sizeStr, "dir")) {
            size[v] = atoi(sizeStr);
        }
    }
}

void processCd() {
    char size[MAXN], path[MAXN];
    scanf(" %s", path);
    if (path[0] == '/') {
        strcpy(pwd, path);
    }
    else if (!strcmp(path, "..")) {
        int i = strlen(pwd)-1;
        for (; pwd[i-1] != '/'; i--);
        pwd[i] = 0;
    }
    else {
        strcat(pwd, path);
        strcat(pwd, "/");
    }
    if (scanf(" $") != EOF) {
        processCmd();
    }
}

void processCmd() {
    char cmd[MAXN];
    scanf(" %s", cmd);
    if (!strcmp(cmd, "ls")) {
        processLs();
    }
    else if (!strcmp(cmd, "cd")) {
        processCd();
    }
}

void dfs(int u) {
    if (g[u].empty()) {
        return;
    }
    size[u] = 0;
    for (int v : g[u]) {
        dfs(v);
        size[u] += size[v];
    }
}

int ans;

void findDir(int u, int minimum) {
    if (g[u].empty()) {
        return;
    }
    if (size[u] >= minimum && size[u] < size[ans]) {
        ans = u;
    }
    for (int v : g[u]) {
        findDir(v, minimum);
    }
}

void print(int u, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s", name[u].c_str());
    if (g[u].empty()) {
        printf(" (file, size=%d)\n", size[u]);
    }
    else {
        printf(" (dir)\n");
    }

    for (int v : g[u]) {
        print(v, depth+1);
    }
}

int main () {
    int root = getNode("/");
    if (scanf(" $") != EOF) {
        processCmd();
    }

    dfs(root);
    int used = size[root];
    int available = 70000000 - used;
    int minimum = 30000000 - available;
    ans = root;
    findDir(root, minimum);

    print(root, 0);
    printf("%d\n", size[ans]);
    return 0;
}