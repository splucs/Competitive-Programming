#define INF 0x3f3f3f3f

class Graph {
private:
    int n;
    vector<vector<int>> dist;
public:
    Graph(int _n, vector<vector<int>>& edges) {
        n = _n;

        // Build adjacency matrix.
        dist.assign(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        for (vector<int> &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            dist[u][v] = w;
        }

        // Initial floyd warshall run.
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    void addEdge(vector<int> edge) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        dist[u][v] = min(dist[u][v], w);
        
        // One floyd warshall run just for the new edge.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][u] + w + dist[v][j]);
            }
        }
    }
    
    int shortestPath(int u, int v) {
        if (dist[u][v] == INF) {
            return -1;
        }
        return dist[u][v];
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
