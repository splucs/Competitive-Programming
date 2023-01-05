#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;

//Treap para arvore binária de busca
struct node{
	string name;
	ii x;
	int y, size;
	node *l, *r;
	node(ii _x, string _name){
		name = _name;
		x = _x;
		y = rand();
		size = 1;
		l = r = NULL;
	}	
};

//10 vezes mais lento que Red-Black....
//Tome uma array de pontos (x,y) ordenados por x. u é ancestral de v se e somente se y(u) é maior que todos os elementos de u a v, v incluso!
//Split separa entre k-1 e k.
class Treap{
private:
	node* root;
	void refresh(node* t){
		if (t == NULL) return;
		t->size = 1;
		if (t->l != NULL)
			t->size += t->l->size;
		if (t->r != NULL)
			t->size += t->r->size;
	}
	void split(node* &t, ii k, node* &a, node* &b){
		node * aux;
		if(t == NULL){
			a = b = NULL;
			return;
		}
		else if(t->x < k){
			split(t->r, k, aux, b);
			t->r = aux;
			refresh(t);
			a = t;
		}
		else{
			split(t->l, k, a, aux);
			t->l = aux;
			refresh(t);
			b = t;
		}
	}
	node* merge(node* &a, node* &b){
		node* aux;
		if(a == NULL) return b;
		else if(b == NULL) return a;
		if(a->y < b->y){
			aux = merge(a->r, b);
			a->r = aux;
			refresh(a);
			return a;
		}
		else{
			aux = merge(a, b->l);
			b->l = aux;
			refresh(b);
			return b;
		}
	}
	node* count(node* t, ii k){
		if(t == NULL) return NULL;
		else if(k < t->x) return count(t->l, k);
		else if(k == t->x) return t;
		else return count(t->r, k);
	}
	int size(node* t){
		if (t == NULL) return 0;
		else return t->size;
	}
	node* nth_element(node* t, int n){
		if (t == NULL) return NULL;
		if(n <= size(t->l)) return nth_element(t->l, n);
		else if(n == size(t->l) + 1) return t;
		else return nth_element(t->r, n-size(t->l)-1);
	}
	void del(node* &t){
		if (t == NULL) return;
		if (t->l != NULL) del(t->l);
		if (t->r != NULL) del(t->r);
		delete t;
		t = NULL;
	}
public:
	Treap(){ root = NULL; }
	~Treap(){ clear(); }
	void clear(){ del(root); }
	int size(){ return size(root); }
	bool insert(ii k, string name){
		if(count(root, k) != NULL) return false;
		node *a, *b, *c, *d;
		split(root, k, a, b);
		c = new node(k, name);
		d = merge(a, c);
		root = merge(d, b);
		return true;
	}
	bool erase(ii k){
		node * f = count(root, k);
		if(f == NULL) return false;
		node *a, *b, *c, *d;
		split(root, k, a, b);
		split(b, ii(k.first, k.second+1), c, d);
		root = merge(a, d);
		delete f;
		return true;
	}
	string nth_element(int n){
		node* ans = nth_element(root, n);
		if (ans == NULL) return nth_element(size());
		else return ans->name;
	}

};

map<string, ii> sec;
char op[20], code[50];

int main() {
	int N, curid = 0;
	scanf("%d", &N);
	Treap tr;

	while(N --> 0) {
		scanf(" %s", op);

		if (!strcmp(op, "ISSUE")) {
			scanf(" %s", code);
			if (sec.count(code)) {
				printf("EXISTS %d %d\n", sec[code].second, -sec[code].first);
			}
			else {
				printf("CREATED %d 0\n", curid);
				ii x = ii(0, curid++);
				tr.insert(x, code);
				sec[code] = x;
			}
		}

		if (!strcmp(op, "DELETE")) {
			scanf(" %s", code);
			if (sec.count(code)) {
				printf("OK %d %d\n", sec[code].second, -sec[code].first);
				tr.erase(sec[code]);
				sec.erase(code);
			}
			else {
				printf("BAD REQUEST\n");
			}
		}

		if (!strcmp(op, "RELIABILITY")) {
			int m;
			scanf(" %s %d", code, &m);
			if (sec.count(code)) {
				ii x = sec[code];
				tr.erase(x);
				x.first -= m;
				tr.insert(x, code);
				sec[code] = x;
				printf("OK %d %d\n", sec[code].second, -sec[code].first);
			}
			else {
				printf("BAD REQUEST\n");
			}
		}

		if (!strcmp(op, "FIND")) {
			int n;
			scanf("%d", &n);
			if (sec.empty()) {
				printf("EMPTY\n");
			}
			else {
				string code = tr.nth_element(n+1);
				printf("OK %s %d %d\n", code.c_str(), sec[code].second, -sec[code].first);
			}
		}
	}

	return 0;
}