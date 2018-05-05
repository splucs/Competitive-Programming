#include <iostream>
#include <cassert>
#include <queue>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef pair<int, PII> Extents;

enum dir_t { UP, RIGHT, DOWN, LEFT };
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };
const int ESCAPE = 9999;

int get_edge_direction(PII p, PII q) {
    if (p.first == q.first) 
        return (p.second < q.second) ? UP : DOWN;
    return (p.first < q.first) ? RIGHT: LEFT;
}

Extents get_edge_extents(PII p, PII q, PII o) {
    if (p.first == q.first) 
        return make_pair(p.first + o.first, PII(min(p.second, q.second) + o.second, max(p.second, q.second) + o.second));
    return make_pair(p.second + o.second, PII(min(p.first, q.first) + o.first, max(p.first, q.first) + o.first));
}

int get_num_escaped(const VPII &state) {
    int num_escaped = 0;
    for (size_t i = 0; i < state.size(); ++i)
        if (state[i].first == ESCAPE)
            ++num_escaped;
    return num_escaped;
}

VPII standardize(VPII state) {
    int num_escaped = get_num_escaped(state);
    if (num_escaped >= state.size() - 1)
        return VPII(state.size(), PII(ESCAPE, ESCAPE));

    int ref = -1;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i].first == ESCAPE) continue;
        if (ref == -1) {
            ref = i;
        } else {
            state[i].first -= state[ref].first;
            state[i].second -= state[ref].second;
        }
    }
    state[ref].first = 0;
    state[ref].second = 0;
    return state;
}

bool touching(PII p, PII q) {
    if (p.second < q.first) return false;
    if (q.second < p.first) return false;
    return true;
}

bool overlaps(PII p, PII q) {
    if (p.second <= q.first) return false;
    if (q.second <= p.first) return false;
    return true;
}

void try_moves(VPII state, int direction, int piece, const VVPII &polys, set<VPII> &seen, queue<VPII> &Q) {
    vector<Extents> moving_edge_extents;
    vector<Extents> stationary_edge_extents;

    for (size_t i = 0; i < polys.size(); ++i) {
        for (size_t j = 0; j < polys[i].size(); ++j) {
            PII p = polys[i][j];
            PII q = polys[i][(j + 1) % polys[i].size()];
            int d = get_edge_direction(p, q);
            if (i == piece && d == (direction + 1) % 4) {
                moving_edge_extents.push_back(get_edge_extents(p, q, state[i]));
            } else if (i != piece && state[i].first != ESCAPE && d == (direction + 3) % 4) {
                stationary_edge_extents.push_back(get_edge_extents(p, q, state[i]));
            }
        }
    }

    set<PII> stops;
    for (size_t i = 0; i < moving_edge_extents.size(); ++i) {
        for (size_t j = 0; j < stationary_edge_extents.size(); ++j) {
            const Extents &m = moving_edge_extents[i];
            const Extents &s = stationary_edge_extents[j];
            int pos1 = m.first;
            int pos2 = s.first;
            if (direction == LEFT || direction == DOWN) swap(pos1, pos2);
            if (pos1 > pos2) continue;
            if (!touching(m.second, s.second)) continue;
            stops.insert(PII(pos2 - pos1, overlaps(m.second, s.second)));
        }
    }
   
    for (set<PII>::iterator iter = stops.begin(); iter != stops.end(); ++iter) {
        VPII new_state = state;
        new_state[piece].first += dx[direction] * iter->first;
        new_state[piece].second += dy[direction] * iter->first;
        new_state = standardize(new_state);
        if (seen.find(new_state) == seen.end()) {
            seen.insert(new_state);
            Q.push(new_state);
        }
        if (iter->second) return;
    }
    VPII new_state = state;
    new_state[piece].first = ESCAPE;
    new_state[piece].second = ESCAPE;
    new_state = standardize(new_state);
    if (seen.find(new_state) == seen.end()) {
        seen.insert(new_state);
        Q.push(new_state);
    }
}

bool is_adjacent(const VPII &state, const VVPII &polys, size_t i1, size_t i2) {
    for (size_t j1 = 0; j1 < polys[i1].size(); ++j1) {
        PII p1 = polys[i1][j1];
        PII q1 = polys[i1][(j1 + 1) % polys[i1].size()];
        int d1 = get_edge_direction(p1, q1);
        Extents e1 = get_edge_extents(p1, q1, state[i1]);
        for (size_t j2 = 0; j2 < polys[i2].size(); ++j2) {
            PII p2 = polys[i2][j2];
            PII q2 = polys[i2][(j2 + 1) % polys[i2].size()];
            int d2 = get_edge_direction(p2, q2);
            if (d1 % 2 != d2 % 2) continue;
            Extents e2 = get_edge_extents(p2, q2, state[i2]);
            if (e1.first != e2.first) continue;
            if (touching(e1.second, e2.second)) return true;
        }
    }
    return false;
}

void flood_fill(VI &components, int here, int label, const VPII &state, const VVPII &polys) {
    components[here] = label;
    for (size_t i = here + 1; i < polys.size(); ++i) {
        if (components[i] != -1) continue;
        if (state[i].first == ESCAPE) continue;
        if (!is_adjacent(state, polys, here, i)) continue;
        flood_fill(components, i, label, state, polys);
    }
}

int count_connected_components(const VPII &state, const VVPII &polys) {
    VI components(polys.size(), -1);
    int num_components = 0;
    for (size_t i = 0; i < polys.size(); ++i)
        if (components[i] == -1 && state[i].first != ESCAPE)
            flood_fill(components, i, num_components++, state, polys);
    return num_components;
}

int solve(const VVPII &polys) {
    set<VPII> seen;
    queue<VPII> Q;
    Q.push(VPII(polys.size()));
    VI escaped(polys.size());
    int num_escaped = 0;
    int num_connected_components = polys.size();

    // simple breadth-first search, with some extra steps to limit the search space
    while (!Q.empty()) {
        VPII state = Q.front();
        Q.pop();

        bool skip = false;

        // prune #1: if we've proven that a piece can be separated, then ignore all
        //           states in which that piece has not been separated -- we'll have
        //           to separate this piece eventually anyway
        for (size_t i = 0; !skip && i < state.size(); ++i)
            if (escaped[i] && state[i].first != ESCAPE)
                skip = true;

        // prune #2: consider only moves that do not increase the number of
        //           connected components; generally, it only makes sense to consider
        //           moves where all pieces remain in contact (transitively)
        int num_components = count_connected_components(state, polys);
        if (num_components < num_connected_components) {
            num_connected_components = num_components;
        } else if (num_components > num_connected_components) {
            skip = true;
        }
        if (skip) continue;

        // prune #3: count up the number of escaped pieces, if we managed to
        //           separate everything, no need to continue
        for (size_t i = 0; i < state.size(); ++i) {
            if (!escaped[i] && state[i].first == ESCAPE) {
                escaped[i] = true;
                ++num_escaped;
            }
        }
        if (num_escaped == polys.size()) break;

        // try moving each piece in each direction
        for (int i = 0; i < state.size(); ++i) {
            if (state[i].first == ESCAPE) continue;
            for (int d = 0; d < 4; ++d)
                try_moves(state, d, i, polys, seen, Q);
        }
    }
    return num_escaped;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        VVPII polys;
        for (int i = 0; i < n; ++i) {
            int c;
            cin >> c;
            VPII poly;
            for (int j = 0; j < c; ++j) {
                int x, y;
                cin >> x >> y;
                poly.push_back(PII(x, y));
            }
            polys.push_back(poly);
        }
        cout << solve(polys) << endl;
    }
    return 0;
}
