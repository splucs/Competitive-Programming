#include <cstdio>
struct node{
    int key, height;
    node *left, *right;
    node(int k) {
        key = k; left = right = 0; 
        height = 1;
    }
};

int ls, ld, rs, rd;

class AVLtree{
private:
    node* root;
    int height(node* p) {
        if (p == NULL) return 0;
        return p?p->height:0;
    }
    int bfactor(node* p) {
        if (p == NULL) return 0;
        return height(p->right)-height(p->left);
    }
    void fixheight(node* p) {
        if (p == NULL) return;
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl>hr?hl:hr)+1;
    }
    node* rotateright(node* p) {
        if (p == NULL) return p;
        node* q = p->left;
        if (q == NULL) return p;
        rs++;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }
    node* rotateleft(node* q) {
        if (q == NULL) return q;
        node* p = q->right;
        if (p == NULL) return q;
        ls++;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }
    node* balance(node* p) {
        if (p == NULL) return 0;
        fixheight(p);
        if(bfactor(p)==2){
            if(bfactor(p->right)<0){
                p->right = rotateright(p->right);
                ls--;
                rs--;
                ld++;
            }
            return rotateleft(p);
        }
        if(bfactor(p)==-2){
            if(bfactor(p->left)>0){
                p->left = rotateleft(p->left);
                rs--;
                ls--;
                rd++;
            }
            return rotateright(p);
        }
        return p;
    }
    node* build(node* p, int k) {
        if(!p) return new node(k);
        if (p->key == k) return p;
        else if(k<p->key) p->left = build(p->left, k);
        else p->right = build(p->right, k);
        return balance(p);
    }
    void inorder(node * p){
        if (p == NULL) return;
        printf("(%d)", p->key);
        inorder(p->left);
        inorder(p->right);
    }
public:
    AVLtree(){ root = 0; }
    void clear(){
        root = 0;
    }
    void insert(int key){
        root = build(root, key);
    }
    void inorder() {
        inorder(root);
        printf("\n");
    }
};

int main(){
    int N, A;
    rd = rs = ls = ld = 0;
    scanf("%d", &N);
    AVLtree tree;
    for(int i=0; i<N; i++){
        scanf("%d", &A);
        //printf("inserting %d\n", A);
        tree.insert(A);
        //tree.inorder();
    }
    tree.inorder();
    printf("%d %d %d %d\n", rs, ls, rd, ld);
    return 0;
}