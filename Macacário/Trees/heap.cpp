#define swap(a, b) {int _x = a; a=b; b=_x;}
#define MAXN 100009

int dist[MAXN];
//função de prioridade, equivale a 'menor que'
bool comp(int a, int b) {
	return dist[a] < dist[b];
}

class Heap{
private:
	int heap[MAXN];
	int inv[MAXN];
	int heapsize;
	void sifup(int n) {
		int k = n << 1;
		while (k <= heapsize) {
			if (k < heapsize && comp(heap[k+1], heap[k])) k++;
			if (comp(heap[k], heap[n])) {
				swap(heap[n], heap[k]);
				inv[heap[n]]=n;
				n = inv[heap[k]]=k;
				k <<= 1;
			}
			else break;
		}
	}
	void sifdown(int n) {
		int k = n >> 1;
		while (k) {
			if (comp(heap[n], heap[k])) {
				swap(heap[n], heap[k]);
				inv[heap[n]]=n;
				n = inv[heap[k]]=k;
				k >>= 1;
			}
			else break;
		}
	}
public:
	Heap() { heapsize = 0; }
	void clear() { heapsize = 0; }
	bool empty() { return heapsize==0; }
	void update(int n) {
		if (inv[n]>heapsize) return;
		sifup(inv[n]);
		sifdown(inv[n]);
	}
	void push(int n) {
		heap[++heapsize] = n;
		inv[n] = heapsize;
		sifdown(heapsize);
	}
	bool count(int n) {
		int k = inv[n];
		return k <= heapsize && k > 0 && heap[k] == n;
	}
	int top() {
		if (heapsize <=0) return -1;
		return heap[1];
	}
	void pop() {
		if (heapsize<=0) return;
		heap[1] = heap[heapsize--];
		inv[heap[1]] = 1;
		sifup(1);
	}
};