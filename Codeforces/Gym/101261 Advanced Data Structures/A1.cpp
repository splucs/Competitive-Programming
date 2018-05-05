#include <bits/stdc++.h>
using namespace std;

struct PNode {
	const int data, depth;
	std::vector<PNode*> par;
	PNode(int _data, int _depth) :
		data(_data), depth(_depth) { }
};
	
class PersistentDeque {
private:
	std::vector<PNode*> front, back;
	std::vector<PNode*> nodes;
	PNode *Newnode(PNode *parent, int data) {
		PNode *node;
		if (parent != NULL) {
			node = new PNode(data, parent->depth + 1);
			node->par.push_back(parent);
			for(int i = 1; i-1 < (int)node->par[i-1]->par.size(); i++) {
				node->par.push_back(node->par[i-1]->par[i-1]);
			}
		}
		else node = new PNode(data, 1);
		nodes.push_back(node);
		return node;
	}
	PNode *LowestCommonAncestor(PNode *u, PNode *v) {
		if (u == NULL || v == NULL) return NULL;
		u = LevelAncestor(u, u->depth - v->depth);
		v = LevelAncestor(v, v->depth - u->depth);
		if (u == v) return u;
		for(int i = int(u->par.size()) - 1; i>= 0; i--) {
			while(i < (int)u->par.size() && u->par[i] != v->par[i]) {
				u = u->par[i];
				v = v->par[i];
			}
		}
		return u->par[0];
	}
	PNode *LevelAncestor(PNode *node, int jump) {
		if (node == NULL || jump <= 0) return node;
		for(int i = 0; i < (int)node->par.size(); i++) {
			if (jump & (1<<i)) {
				node = node->par[i];
			}
		}
		return node;
	}
public:
	PersistentDeque() { Clear(); }
	~PersistentDeque() { Clear(); }
	void Clear() {
		for(int i = 0; i < (int)nodes.size(); i++) {
			delete nodes[i];
		}
		nodes.clear();
		back.clear(); back.push_back(NULL);
		front.clear(); front.push_back(NULL);
	}
	int Front(int ver) {
		return front[ver]->data;
	}
	int Back(int ver) {
		return back[ver]->data;
	}
	int PopFront(int ver) {
		if (front[ver] == back[ver]) {
			back.push_back(NULL);
			front.push_back(NULL);
			return int(front.size())-1;
		}
		PNode *lca = LowestCommonAncestor(front[ver], back[ver]);
		back.push_back(back[ver]);
		if (front[ver] == lca) {
			PNode *la = LevelAncestor(back[ver], back[ver]->depth - lca->depth - 1);
			front.push_back(la);
		}
		else front.push_back(front[ver]->par[0]);
		return int(front.size())-1;
	}
	int PopBack(int ver) {
		if (front[ver] == back[ver]) {
			back.push_back(NULL);
			front.push_back(NULL);
			return int(back.size())-1;
		}
		PNode *lca = LowestCommonAncestor(front[ver], back[ver]);
		front.push_back(front[ver]);
		if (back[ver] == lca) {
			PNode *la = LevelAncestor(front[ver], front[ver]->depth - lca->depth - 1);
			back.push_back(la);
		}
		else back.push_back(back[ver]->par[0]);
		return int(back.size())-1;
	}
	int PushFront(int ver, int data) {
		PNode *node = Newnode(front[ver], data);
		front.push_back(node);
		if (back[ver] == NULL) back.push_back(node);
		else back.push_back(back[ver]);
		return int(front.size()) - 1;
	}
	int PushBack(int ver, int data) {
		PNode *node = Newnode(back[ver], data);
		back.push_back(node);
		if (front[ver] == NULL) front.push_back(node);
		else front.push_back(front[ver]);
		return int(back.size()) - 1;
	}
	int At(int ver, int i) {
		PNode *lca = LowestCommonAncestor(front[ver], back[ver]);
		int frontDist = front[ver]->depth - lca->depth;
		int backDist = back[ver]->depth - lca->depth;
		PNode *node;
		if (i <= frontDist) node = LevelAncestor(front[ver], i);
		else node = LevelAncestor(back[ver], frontDist + backDist - i);
		return node->data;
	}
	int Size(int ver) {
		PNode *lca = LowestCommonAncestor(front[ver], back[ver]);
		if (lca == NULL) return 0;
		return front[ver]->depth + back[ver]->depth - 2*lca->depth + 1;
	}
	int LatestVersion() {
		return int(back.size())-1;
	}
};

int main() {
	int Q, ver, val;
	scanf("%d", &Q);
	char op;
	PersistentDeque pd;
	while (Q --> 0) {
		scanf(" %c", &op);
		if (op == 'B') {
			scanf("%d %d", &ver, &val);
			pd.PushFront(ver, val);
		}
		if (op == 'E') {
			scanf("%d %d", &ver, &val);
			pd.PushBack(ver, val);
		}
		if (op == '<') {
			scanf("%d", &ver);
			val = pd.Front(ver);
			pd.PopFront(ver);
			printf("%d\n", val);
			fflush(stdout);
		}
		if (op == '>') {
			scanf("%d", &ver);
			val = pd.Back(ver);
			pd.PopBack(ver);
			printf("%d\n", val);
			fflush(stdout);
		}
	}
	return 0;
}