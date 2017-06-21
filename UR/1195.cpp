#include <cstdio>
#include <cstdlib>
class node{
public:
    node(int n){
        value = n;
        right = left = NULL;
    }
    virtual ~node(){
        if (right!=NULL) delete right;
        if (left!=NULL) delete left;
    }
    int value;
    node* left;
    node* right;
};
node* add(int n, node* p){
    if(p==NULL) return new node(n);
    if (p->value==n) return p;
    if (p->value<n) p->right = add(n, p->right);
    if (p->value>n) p->left = add(n, p->left);
    return p;
}
void preorder(node* p){
    if (p==NULL) return;
    printf(" %d", p->value);
    preorder(p->left);
    preorder(p->right);
}
void inorder(node* p){
    if (p==NULL) return;
    inorder(p->left);
    printf(" %d", p->value);
    inorder(p->right);
}
void posorder(node* p){
    if (p==NULL) return;
    posorder(p->left);
    posorder(p->right);
    printf(" %d", p->value);
}
int main()
{
    int C, N, x;
    node* root;
    scanf("%d", &C);
    for (int caso=1; caso<=C; caso++){
        scanf("%d", &N);
        root=NULL;
        for (int i=0; i<N; i++){
            scanf("%d", &x);
            root=add(x, root);
        }
        printf("Case %d:\nPre.:", caso);
        preorder(root);
        printf("\nIn..:");
        inorder(root);
        printf("\nPost:");
        posorder(root);
        printf("\n\n");
        delete root;
    }
    return 0;
}
