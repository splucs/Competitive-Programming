#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <utility>      // std::pair
using namespace std;

#define MAX_N 100005
#define MAX 1000000 // Why? :D
#define inf 0x7fffffff

struct node_st {
	int l, r, acum;
	int child;
};

pair<int, int> arr[MAX_N];
node_st tree[MAX];
node_st lazy[MAX];

/**
 * Build and init tree
 */
void build_tree(int node, int a, int b) {
  	if(a > b) {
  		return; // Out of range
  	}

  	if(a == b) { // Leaf node
    		tree[node].l = arr[a].first; // Init value
    		tree[node].r = arr[a].first; // Init value
    		tree[node].acum = arr[a].second; // Init value
    		tree[node].child = 1;
		return;
	}
	
	build_tree(node*2, a, (a+b)/2); // Init left child
	build_tree(node*2+1, 1+(a+b)/2, b); // Init right child
	
	tree[node].l = min(tree[node*2].l, tree[node*2 + 1].l);
	tree[node].r = max(tree[node*2].r, tree[node*2 + 1].r);
	tree[node].acum = tree[node*2].acum^tree[node*2 + 1].acum;
	tree[node].child = tree[node*2].child + tree[node*2+1].child;
}

/**
 * Decrement elements bigger than x
 */
void update_tree(int node, int a, int b, int x, int value) {
  
  	if(lazy[node].acum != 0) { // This node needs to be updated
   		tree[node].l += lazy[node].l; // Update it
   		tree[node].r += lazy[node].r; // Update it
   		if (tree[node].child%2 == 1) tree[node].acum ^= lazy[node].acum; // Update it

		if(a != b) {
    		lazy[node*2].l += lazy[node].l;
    		lazy[node*2].r += lazy[node].r;
    		lazy[node*2].acum ^= lazy[node].acum;

    		lazy[node*2+1].l += lazy[node].l;
    		lazy[node*2+1].r += lazy[node].r;
    		lazy[node*2+1].acum ^= lazy[node].acum;
		}

   		lazy[node].l = 0; // Reset it
   		lazy[node].r = 0; // Reset it
   		lazy[node].acum = 0; // Reset it
  	}

	if(tree[node].r < x) // Nothing to be done
		return;
    
    if(tree[node].l >= x) { // Must update all
    	tree[node].l -= x;
    	tree[node].r -= x;
	   	if (tree[node].child%2 == 1) tree[node].acum ^= value;

    	if (a != b) {
    		lazy[node*2].l -= x;
    		lazy[node*2].r -= x;
    		lazy[node*2].acum ^= value;

    		lazy[node*2+1].l -= x;
    		lazy[node*2+1].r -= x;
    		lazy[node*2+1].acum ^= value;
    	}
    	return;
    }

	update_tree(node*2, a, (a+b)/2, x, value); // Updating left child
	update_tree(1+node*2, 1+(a+b)/2, b, x, value); // Updating right child

	tree[node].l = min(tree[node*2].l, tree[node*2 + 1].l);
	tree[node].r = max(tree[node*2].r, tree[node*2 + 1].r);
	tree[node].acum = tree[node*2].acum^tree[node*2 + 1].acum;
}

/**
 * Query tree
 */
int query_tree(int node, int a, int b, int x) {
	if(tree[node].r < x) return 0; // Out of range

	if(lazy[node].acum != 0) { // This node needs to be updated
   		tree[node].l += lazy[node].l; // Update it
   		tree[node].r += lazy[node].r; // Update it
	   	if (tree[node].child%2 == 1) tree[node].acum ^= lazy[node].acum; // Update it

		if(a != b) {
    		lazy[node*2].l += lazy[node].l;
    		lazy[node*2].r += lazy[node].r;
    		lazy[node*2].acum ^= lazy[node].acum;

    		lazy[node*2+1].l += lazy[node].l;
    		lazy[node*2+1].r += lazy[node].r;
    		lazy[node*2+1].acum ^= lazy[node].acum;
		}

   		lazy[node].l = 0; // Reset it
   		lazy[node].r = 0; // Reset it
   		lazy[node].acum = 0; // Reset it
  	}

	if(tree[node].l >= x) // Current segment is totally within range [i, j]
		return tree[node].acum;

	int q1 = query_tree(node*2, a, (a+b)/2, x); // Query left child
	int q2 = query_tree(1+node*2, 1+(a+b)/2, b, x); // Query right child

	int res = q1^q2; // Return final result
	
	return res;
}

int main() {
	int n, q;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
	}

	sort(arr, arr + n);
	build_tree(1, 0, n-1);

	memset(lazy, 0, sizeof lazy);

	scanf("%d", &q);
	while(q--) {
		int t, x, val;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d %d", &x, &val);
			update_tree(1, 0, n-1, x, val); // Increment range [10, N-1] by 100. here 0, N-1 represent the current range.
		} else {
			scanf("%d", &x);
			printf("%d\n", query_tree(1, 0, n-1, x)); // Get max element in range [0, N-1]
		}
	}
}