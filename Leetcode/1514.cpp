typedef pair<double, int> pdi;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pdi>> g(n);
        int m = edges.size();

        // Build graph
        for (int j = 0; j < m; j++) {
            int u = edges[j][0];
            int v = edges[j][1];
            double w = -log(succProb[j]);

            g[u].push_back(pdi(w, v));
            g[v].push_back(pdi(w, u));
        }
        
        // Set up dijstra's algorithm
        set<pdi> s;
        vector<double> dist(n, DBL_MAX);
        s.insert(pdi(0, start));
        dist[start] = 0;

        // Run dijkstra's algorithm
        while(!s.empty()) {
            pdi cur = *s.begin();
            s.erase(cur);
            int u = cur.second;
            if (u == end) {
                return exp(-dist[u]);
            }
    
            for (pdi e : g[u]) {
                double w = e.first;
                int v = e.second;
                if (dist[v] > dist[u] + w) {
                    if (s.count(pdi(dist[v], v))) s.erase(pdi(dist[v], v));
                    dist[v] = dist[u] + w;
                    s.insert(pdi(dist[v], v));
                }
            }
        }
        
        return 0;
    }
};
