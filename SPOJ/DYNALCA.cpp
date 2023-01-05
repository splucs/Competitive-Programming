#include <cstdio>
#include <vector>
using namespace std;
#define INF (1<<30)

struct node
{   int size, id, w; /* size, label */
    node *par, *ppar, *left, *right; /* parent, path-parent, left, right pointers */
    node() {
		par = ppar = left = right = NULL; 
		w = size = INF;
	}
};

class LinkCutTree
{
	vector<node> lct;

	void update(node* p) {
		p->size = p->w;
		if (p->left) p->size += p->left->size;
		if (p->right) p->size += p->right->size;
	}

	void rotateright(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if ((q->left = p->right)) q->left->par = q;
		p->right = q, q->par = p;
		if ((p->par = r)) {
			if (q == r->left) r->left = p;
			else r->right = p;
		}
		p->ppar = q->ppar;
		q->ppar = NULL;
		update(q);
	}

	void rotateleft(node* p) {
		node *q, *r;
		q = p->par, r = q->par;
		if ((q->right = p->left)) q->right->par = q;
		p->left = q, q->par = p;
		if ((p->par = r))
		{
			if (q == r->left) r->left = p;
			else r->right = p;
		}
		p->ppar = q->ppar;
		q->ppar = 0;
		update(q);
	}

	void splay(node* p) {
		node *q, *r;
		while (p->par != NULL) {
			q = p->par;
			if (q->par == NULL) {
				if (p == q->left) rotateright(p);
				else rotateleft(p);
			}
			else {
				r = q->par;
				if (q == r->left) {
					if (p == q->left) rotateright(q), rotateright(p);
					else rotateleft(p), rotateright(p);
				}
				else {
					if (p == q->right) rotateleft(q), rotateleft(p);
					else rotateright(p), rotateleft(p);
				}
			}
		}
		update(p);
	}

	node* access(node* p){
		splay(p);
		if (p->right != NULL) {
			p->right->ppar = p;
			p->right->par = NULL;
			p->right = NULL;
			update(p);
		}
		node* last = p;
		while (p->ppar != NULL) {
			node* q = p->ppar;
			last = q;
			splay(q);
			if (q->right != NULL) {
				q->right->ppar = q;
				q->right->par = NULL;
			}
			q->right = p;
			p->par = q;
			p->ppar = NULL;
			update(q);
			splay(p);
		}
		return last;
	}

public:
    LinkCutTree(int n) {
		lct.resize(n + 1);
        for(int i = 0; i <= n; i++){
			lct[i].id = i;
            update(&lct[i]);
        }
    }

	void link(int u, int v, int w) { //u becomes child of v
		node *p = &lct[u], *q = &lct[v];
		access(p);
		access(q);
		p->left = q;
		q->par = p;
		p->w = w;
		update(p);
	}

	void link(int u, int v) { //u becomes child of v
		link(u, v, 1);
	}

    void cut(int u) {
		node* p = &lct[u];
		access(p);
		p->left->par = NULL;
		p->left = NULL;
		update(p);
    }

    int findroot(int u) {
		node* p = &lct[u];
		access(p);
		while (p->left) p = p->left;
		splay(p);
		return p->id;
    }

	bool IsSameTree(int u, int v) {
		return findroot(u) == findroot(v);
	}

    int depth(int u) {
		access(&lct[u]);
		return lct[u].size - lct[u].w;
    }

    int LCA(int u, int v) {
		access(&lct[u]);
		return access(&lct[v])->id;
    }
};

int main()
{
	int N, M, u, v;
	char str[10];
	scanf("%d %d", &N, &M);
	LinkCutTree lct(N+1);
	for(int i=0; i<M; i++){
		scanf(" %s", str);
		if(str[1] == 'i'){
			scanf("%d %d", &u, &v);
			lct.link(u, v);
		}
		if(str[1] == 'u'){
			scanf("%d", &u);
			lct.cut(u);
		}
		if (str[1] == 'c'){
			scanf("%d %d", &u, &v);
			printf("%d\n", lct.LCA(u, v));
		}
	}
	return 0;
}