#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

//Treap para arvore binária de busca
struct node{
	int x, y, size;
	node *l, *r;
	node(int _x){
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
	void split(node* &t, int k, node* &a, node* &b){
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
	node* count(node* t, int k){
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
	bool count(int k){ return count(root, k) != NULL; }
	bool insert(int k){
		if(count(root, k) != NULL) return false;
		node *a, *b, *c, *d;
		split(root, k, a, b);
		c = new node(k);
		d = merge(a, c);
		root = merge(d, b);
		return true;
	}
	bool erase(int k){
		node * f = count(root, k);
		if(f == NULL) return false;
		node *a, *b, *c, *d;
		split(root, k, a, b);
		split(b, k+1, c, d);
		root = merge(a, d);
		delete f;
		return true;
	}
	int nth_element(int n){
		node* ans = nth_element(root, n);
		if (ans == NULL) return -1;
		else return ans->x;
	}

};

int vet[10000009];

void test(){
	set<int> s;
	Treap t;
	int N = 1000000;
	for(int i=0; i<N; i++){
		int n = rand()%1000;
		if(!s.count(n)){
			s.insert(n);
			t.insert(n);
			//if(!t.insert(n)) printf("error inserting %d in treap!\n", n);
			//printf("inserted %d\n", n);
		}
		else{
			s.erase(n);
			t.erase(n);
			//if(!t.erase(n)) printf("error erasing %d in treap!\n", n);
			//printf("erased %d\n", n);
		}
		n = rand()%1000;
		if (s.count(n) != t.count(n)){
			printf("failed test %d, s.count(%d) = %d, t.count(%d) = %d\n", i, n, s.count(n), n, t.count(n));
		}
	}
	s.clear();
	t.clear();
	for(int i=0; i<N; i++){
		vet[i] = i+1;
	}
	random_shuffle(vet, vet+N);
	for(int i=0; i<N; i++){
		t.insert(vet[i]);
	}
	for(int i=1; i<=N; i++){
		if (t.nth_element(i) != i){
			printf("failed test %d\n", i);
		}
	}
}

int main(){
	test();
	return 0;
}
