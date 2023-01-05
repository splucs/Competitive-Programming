#include <bits/stdc++.h>
using namespace std;

inline int max(int x, int y) {
    return x < y ? y : x;
}

struct robot {
    int cost[4];
    robot() {
        for (int i = 0; i < 4; i++) cost[i] = 0;
    }
};

struct blueprint {
    int id;
    robot robots[4];
    blueprint(int _id) : id(_id) {
        for (int i = 0; i < 4; i++) robots[i] = robot();
    }
};

vector<blueprint> readInput() {
    vector<blueprint> bps;
    int id;
    while (scanf(" Blueprint %d:", &id) != EOF) {
        blueprint bp(id);
        scanf(" Each ore robot costs %d ore.", &bp.robots[0].cost[0]);
        scanf(" Each clay robot costs %d ore.", &bp.robots[1].cost[0]);
        scanf(" Each obsidian robot costs %d ore and %d clay.", &bp.robots[2].cost[0], &bp.robots[2].cost[1]);
        scanf(" Each geode robot costs %d ore and %d obsidian.", &bp.robots[3].cost[0], &bp.robots[3].cost[2]);
        bps.push_back(bp);
    }
    return bps;
}

int resources[4], robotCount[4];

inline void apply() {
    for(int r = 0; r < 4; r++) resources[r] += robotCount[r];
}

inline void unapply() {
    for(int r = 0; r < 4; r++) resources[r] -= robotCount[r];
}

inline bool canBuild(blueprint &bp, int r) {
    for(int c = 0; c < 4; c++) {
        if (resources[c] < bp.robots[r].cost[c]) {
            return false;
        }
    }
    return true;
}

inline bool isUseful(blueprint &bp, int r, int m) {
    if (r == 3) { // geode is always useful
        return true;
    }
    int mostExpensive = 0;
    for (int c = 0; c < 4; c++) {
        mostExpensive = max(mostExpensive, bp.robots[c].cost[r]);
    }

    int mostRequired = (m-1)*mostExpensive;
    if (resources[r] + (robotCount[r]*(m-1)) >= mostRequired) {
        return false;
    }

    return true;
}

inline void build(blueprint &bp, int r) {
    robotCount[r]++;
    for(int c = 0; c < 4; c++) {
        resources[c] -= bp.robots[r].cost[c];
    }
}

inline void unbuild(blueprint &bp, int r) {
    robotCount[r]--;
    for(int c = 0; c < 4; c++) {
        resources[c] += bp.robots[r].cost[c];
    }
}

int recurse(blueprint &bp, int m) {
    if (m == 1) {
        // not worth building anything
        apply();
        int ans = resources[3];
        unapply();
        return ans;
    }

    int ans = 0;

    // try to build robots
    for(int r = 3; r >= 0; r--) {
        if (!canBuild(bp, r) || !isUseful(bp, r, m)) {
            continue;
        }
        apply();
        build(bp, r);
        ans = max(ans, recurse(bp, m-1));
        unbuild(bp, r);
        unapply();
    }

    // do nothing
    apply();
    ans = max(ans, recurse(bp, m-1));
    unapply();

    return ans;
}

int main() {
    int ans = 0;
    for(blueprint &bp : readInput()) {
        memset(resources, 0, sizeof resources);
        memset(robotCount, 0, sizeof robotCount);
        robotCount[0] = 1;

        ans += bp.id*recurse(bp, 24);
    }
    printf("%d\n", ans);
    return 0;
}