#define INFLL 0x3f3f3f3f3f3f3f3f

class FlowNetwork {
private:
    int n;
    vector<int> first, to, nxt, prv, vis;
    vector<long long> cap, cost, dist; 
    vector<bool> inq;

    bool spfa(int s, int t) {
        dist.assign(n, INFLL);
        vis.assign(n, 0);
        inq.assign(n, false);
        prv.assign(n, -1);
	    queue<int> q;
	    q.push(s);
	    dist[s] = 0;
	    inq[s] = true;
	    while (!q.empty()) {
		    int u = q.front(); q.pop();
		    if (vis[u] > n) return false;
		    inq[u] = false;
		    for (int e = first[u]; e != -1; e = nxt[e]) {
                if (cap[e] <= 0) continue;
			    int v = to[e];
                int w = cost[e];
			    if (dist[u] + w < dist[v]) {
				    dist[v] = dist[u] + w;
                    prv[v] = e;
				    if (!inq[v]) {
					    vis[v]++;
                        q.push(v);
					    inq[v] = true;
				    }
			    }
		    }
	    }
	    return dist[t] < INFLL;
    }

    long long augment(int s, int t, long long &maxflow) {
	    long long flow = maxflow;
	    for(int i = t; i != s; i = to[prv[i]^1])
		    flow = min(flow, cap[prv[i]]);
    	for(int i = t; i != s; i = to[prv[i]^1]) {
    		cap[prv[i]] -= flow;
    		cap[prv[i]^1] += flow;
    	}
    	maxflow -= flow;
    	long long flowCost = flow*dist[t];
    	return flowCost;
    }

public:
    FlowNetwork(int _n) {
        n = _n;
        first.assign(n, -1);
    }

    void add(int u, int v, long long f, long long c) {
        to.push_back(v);
        cap.push_back(f);
        cost.push_back(c);
        nxt.push_back(first[u]);
        first[u] = to.size()-1;
  
        to.push_back(u);
        cap.push_back(0);
        cost.push_back(-c);
        nxt.push_back(first[v]);
        first[v] = to.size()-1;
    }

    long long mincostmaxflow(int s, int t, long long maxflow) {
	    long long flowCost = 0;
	    while(maxflow > 0 && spfa(s, t)) {
		    flowCost += augment(s, t, maxflow);
	    }
	    return flowCost;
    }
};

class Solution {
private:
    long long abs(long long x) {
        return x < 0 ? -x : x;
    }
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int n = robot.size(), m = factory.size();
        FlowNetwork f(1 + n + m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                f.add(i, n+j, 1, abs(robot[i] - factory[j][0]));
            }
        }
        for (int j = 0; j < m; j++) {
            f.add(n+j, n+m, factory[j][1], 0);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += f.mincostmaxflow(i, n+m, 1);
        }
        return ans;
    }
};
