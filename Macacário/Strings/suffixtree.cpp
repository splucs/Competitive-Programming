#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
 * Suffix Tree
 * Ukkonen's O(n) algorithm
 */

struct node {
	int l, r, par, link = -1, nsons = 0, next[26];
	node(int l=0, int r=0, int par=-1) : l(l), r(r), par(par) {
		memset(next, -1, sizeof next); 
	}
	inline int reduce(char c) { return c - 'a'; }
	int len() { return r - l; }
	int& get(char c) { return next[reduce(c)]; }
	void setEdge(char c, int i) {
		int rc = reduce(c);
		if (next[rc] != -1 && i == -1) --nsons;
		else if (next[rc] == -1 && i != -1) ++nsons;
		next[rc] = i;
	}
};

struct state {
	int v, pos;
	state(int v, int pos) : v(v), pos(pos) {}
 };

class SuffixTree {
	string text;
	queue<int> qleaves;
	vector<node> tree;
	state ptr = state(0, 0);
	long long num_substr = 0;
	state go(state st, int l, int r) {
		while (l < r) {
			if (st.pos == tree[st.v].len()) {
				st = state(tree[st.v].get(text[l]), 0);
				if (st.v == -1) return st;
			}
			else {
				if (text[tree[st.v].l + st.pos] != text[l])
					return state(-1, -1);
				if (r-l < tree[st.v].len() - st.pos)
					return state(st.v, st.pos + r-l);
				l += tree[st.v].len() - st.pos;
				st.pos = tree[st.v].len();
			}
		}
		return st;
	}
	int split(const state& st) {
		if (st.pos == tree[st.v].len()) return st.v;
		if (st.pos == 0) return tree[st.v].par;
		const node& v = tree[st.v];
		int id = tree.size();
		tree.push_back(node(v.l, v.l + st.pos, v.par));
		tree[v.par].setEdge(text[v.l], id);
		tree[id].setEdge(text[v.l + st.pos], st.v);
		tree[st.v].par = id;
		tree[st.v].l += st.pos;
		return id;
	}
	int getLink(int v) {
		if (tree[v].link != -1) return tree[v].link;
		if (tree[v].par == -1)  return 0;
		int to = getLink(tree[v].par);
		return tree[v].link = split(go(state(to,tree[to].len()), tree[v].l + (tree[v].par==0), tree[v].r));
	}
public:
	SuffixTree(char* str) {
		text = string(str);
		tree.reserve(2 * text.size() + 1);
		tree.push_back(node(0));
	}
	void extend(int pos) {
		int mid;
		num_substr += qleaves.size();
		do {
			state nptr = go(ptr, pos, pos+1);
			if (nptr.v != -1) {
				ptr = nptr; return;
			}
			mid = split(ptr);
			int leaf = tree.size();
			num_substr++;         // new leaf.
			qleaves.push(leaf);
			tree.push_back(node(pos, text.size(), mid));
			tree[mid].setEdge(text[pos], leaf);
			ptr.v = getLink(mid);
			ptr.pos = tree[ptr.v].len();
		} while (mid != 0);
	}

	void pop(int pos) {
		int leaf = qleaves.front();
		qleaves.pop();
		int par = tree[leaf].par;
		while (tree[leaf].nsons == 0) {
			if (ptr.v != leaf) {
				tree[par].setEdge(text[tree[leaf].l], -1);
				num_substr -= min(tree[leaf].r, pos) - tree[leaf].l;
				leaf = par;
				par = tree[leaf].par;
			} else {
				if (ptr.pos == min(tree[leaf].r,pos) - tree[leaf].l)
					break;
				int mid = split(ptr);
				ptr.v = mid;
				num_substr -= min(tree[leaf].r, pos) - tree[leaf].l;
				tree[mid].setEdge(text[tree[leaf].l], -1);
				tree[leaf] = tree[mid];
				tree[tree[mid].par].setEdge(text[tree[mid].l], leaf);
				tree.pop_back();
				break;
			}
		}
		if (leaf != 0 && tree[leaf].nsons == 0) { 
			qleaves.push(leaf);
			int to = (tree[leaf].par == 0) ? 0 : tree[tree[leaf].par].link;
			ptr = go(state(to, tree[to].len()), tree[leaf].l + (tree[leaf].par==0), tree[leaf].r);
			tree[leaf].l = pos - tree[leaf].len();
			tree[leaf].r = text.size();
		}
	}
};

// Usability:
// SuffixTree(text) creates with presetted string
// extend(i) add caracters at text[i] in string
// pop(i) deletes first character from Suffix Tree assuming i letters have been added

// Example (number of substrings in sliding window):
// SuffixTree suffix_tree(text);
// for (int i = 1; i <= (int)suffix_tree.text.size(); ++i) {
//   suffix_tree.extend(i-1);
//   if (i >= w) {
//     suffix_tree.num_substr contains number of substrings;
//     suffix_tree.pop(i);
//   }
// }