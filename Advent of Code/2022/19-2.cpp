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
    for (int b = 0; scanf(" Blueprint %d:", &id) != EOF && b < 3; b++) {
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

inline void apply(int dm) {
    for(int r = 0; r < 4; r++) resources[r] += robotCount[r]*dm;
}

inline void unapply(int dm) {
    for(int r = 0; r < 4; r++) resources[r] -= robotCount[r]*dm;
}

inline bool canBuildWithWait(blueprint &bp, int r) {
    for(int c = 0; c < 4; c++) {
        if (bp.robots[r].cost[c] > 0 && robotCount[c] == 0) {
            return false;
        }
    }
    return true;
}

inline int howLongToBuild(blueprint &bp, int r) {
    int ans = 0;
    for(int c = 0; c < 4; c++) {
        if (bp.robots[r].cost[c] == 0) {
            continue;
        }
        int required = bp.robots[r].cost[c] - resources[c];
        if (required <= 0) {
            continue;
        }
        int bots = robotCount[c];
        int minutes = (required+bots-1)/bots;
        ans = max(ans, minutes);
    }
    return ans;
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
    if (m < 0) {
        return 0;
    }
    if (m == 0) {
        return resources[3];
    }

    int ans = 0;

    // try to build robots
    for(int r = 3; r >= 0; r--) {
        if (!canBuildWithWait(bp, r) || !isUseful(bp, r, m)) {
            continue;
        }
        int dm = howLongToBuild(bp, r);
        if (dm >= m) {
            continue;
        }

        apply(dm+1);
        build(bp, r);
        ans = max(ans, recurse(bp, m-1-dm));
        unbuild(bp, r);
        unapply(dm+1);
    }

    // do nothing
    apply(m);
    ans = max(ans, recurse(bp, 0));
    unapply(m);

    return ans;
}

int main() {
    int ans = 1;
    for(blueprint &bp : readInput()) {
            memset(resources, 0, sizeof resources);
            memset(robotCount, 0, sizeof robotCount);
            robotCount[0] = 1;

            ans *= recurse(bp, 32);
    }
    printf("%d\n", ans);
    return 0;
}