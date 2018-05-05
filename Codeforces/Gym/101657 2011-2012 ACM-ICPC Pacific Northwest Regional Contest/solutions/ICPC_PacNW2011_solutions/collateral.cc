// --------------------------------------------------------------------------
// Collateral Cleanup  [author's O(n lg n) reference solution]
// 2011 Pacific Northwest Regional Programming Contest
//
// Author:  Sonny Chan
// Date:    September 30, 2011
// --------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

// --------------------------------------------------------------------------
// a few useful data structures and operators

struct point {
    int x, y;
    point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};

bool operator<(const point &p, const point &q) {
    if (p.x == q.x) return p.y < q.y;
    return p.x < q.x;
}

bool operator==(const point &p, const point &q) {
    return (p.x == q.x) && (p.y == q.y);
}

istream &operator>>(istream &stream, point &p) {
    return stream >> p.x >> p.y;
}

struct edge {
    point a, b;
    edge(point aa, point bb) : a(aa), b(bb) {}
    edge reverse() const { return edge(b, a); }
    int dx() const { return b.x - a.x; }
};

bool operator<(const edge &e, const edge &f) {
    if (e.a == f.a) return e.b < f.b;
    return e.a < f.a;
}

// --------------------------------------------------------------------------

int main()
{
    istream &in = cin;
    ostream &out = cout;
    
    int walls;
    in >> walls;
    for (int w = 0; w < walls; ++w)
    {
        int n;
        in >> n;
        
        // a hash to detect coincident edges
        map<edge, int> cracks;
        
        // adjacency lists for the triangles
        vector< vector<int> > adj(n);
        
        // read individual triangles and create adjacency lists
        for (int i = 0; i < n; ++i)
        {
            point v[3];
            for (int j = 0; j < 3; ++j)
                in >> v[j];
            
            // go through 3 edges of each triangle
            for (int j = 0; j < 3; ++j)
            {
                edge e(v[j], v[(j+1)%3]);
                
                // test if reverse edge has already been seen
                if (cracks.find(e.reverse()) == cracks.end())
                    cracks[e] = i;
                else {
                    int t = cracks[e.reverse()];
                    // establish the ordering this edge imposes
                    if (e.dx() > 0)         adj[i].push_back(t);
                    else if (e.dx() < 0)    adj[t].push_back(i);
                }
            }
        }
        
        // do topological sort to determine a feasible ordering of the triangles
        vector<bool> seen(n, false), sent(n, false);
        vector<int> sorted;
        stack<int> st;
        for (int i = 0; i < n; ++i)
        {
            if (seen[i]) continue;
            st.push(i);
            while (!st.empty())
            {
                int s = st.top();
                
                if (seen[s]) {      // was traversed already
                    st.pop();
                    if (!sent[s]) {
                        sorted.push_back(s);
                        sent[s] = true;
                    }
                }
                else {              // traverse dependencies
                    vector<int> &a = adj[s];
                    for (int j = 0; j < a.size(); ++j)
                        if (!seen[a[j]]) st.push(a[j]);
                }
                    
                seen[s] = true;     // mark as traversed
            }
        }
        
        // output result, adding one to the indices
        for (int i = 0; i < sorted.size(); ++i) {
            if (i != 0) out << ' ';
            out << sorted[i]+1;
        }
        out << endl;
    }
    
    return 0;
}

// --------------------------------------------------------------------------
