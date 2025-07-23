class Solution {
private:
    vector<int> edges;
    int findDistTo(int u, int v) {
        int n = edges.size();
        vector<bool> seen(n, false);
        int ans = 0;
        for(; u != v; u = edges[u]) {
            if (seen[u]) {
                return -1;
            }
            seen[u] = true;
            ans++;
            if (edges[u] == -1) {
                return -1;
            }
        }
        return ans;
    }
    int findStartOfCycle(int u) {
        int n = edges.size();
        vector<bool> seen(n, false);
        for(; true; u = edges[u]) {
            if (seen[u]) {
                return u;
            }
            seen[u] = true;
            if (edges[u] == -1) {
                return u;
            }
        }
        return -1;
    }
public:
    int closestMeetingNode(vector<int>& _edges, int node1, int node2) {
        edges.swap(_edges);
        int root1 = findStartOfCycle(node1);
        int root2 = findStartOfCycle(node2);
        int dist1 = findDistTo(node1, root2);
        int dist2 = findDistTo(node2, root1);

        if (root1 == root2) {
            while (dist1 > dist2) {
                dist1--;
                node1 = edges[node1];
            }
            while (dist1 < dist2) {
                dist2--;
                node2 = edges[node2];
            }
            while (node1 != node2) {
                node1 = edges[node1];
                node2 = edges[node2];
            }
            return node1;
        }

        if (dist1 == -1) {
            return -1;
        }
        if (dist1 == dist2) {
            return min(root1, root2);
        }
        return dist1 < dist2 ? root2 : root1;
    }
};
