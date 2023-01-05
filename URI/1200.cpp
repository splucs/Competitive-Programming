#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
class node{
public:
    node(char n){
        value = n;
        right = left = NULL;
    }
    virtual ~node(){
        if (right!=NULL) delete right;
        if (left!=NULL) delete left;
    }
    char value;
    node* left;
    node* right;
};
char temp[5];
char order[5000];
bool exists(char c, node* p){
    if (p==NULL) return false;
    else if (p->value==c) return true;
    else if (c>p->value) return exists(c, p->right);
    else return exists(c, p->left);
}
node* add(char n, node* p){
    if(p==NULL) return new node(n);
    if (p->value==n) return p;
    if (p->value<n) p->right = add(n, p->right);
    if (p->value>n) p->left = add(n, p->left);
    return p;
}
void preorder(node* p){
    if (p==NULL) return;
    sprintf(temp, "%c ", p->value);
    strcat(order, temp);
    preorder(p->left);
    preorder(p->right);
}
void inorder(node* p){
    if (p==NULL) return;
    inorder(p->left);
    sprintf(temp, "%c ", p->value);
    strcat(order, temp);
    inorder(p->right);
}
void posorder(node* p){
    if (p==NULL) return;
    posorder(p->left);
    posorder(p->right);
    sprintf(temp, "%c ", p->value);
    strcat(order, temp);
}
int main()
{
    char word[10];
    char x;
    node* root=NULL;
    bool aux;
    while (scanf(" %s", word)!=EOF){
        if (!strcmp(word, "I")){
            cin>>x;
            root=add(x, root);
        }
        if (!strcmp(word, "P")){
            cin>>x;
            aux = exists(x, root);
            if (aux) printf("%c existe\n", x);
            else printf("%c nao existe\n", x);
        }
        if(!strcmp(word, "INFIXA")){
            strcpy(order, "");
            inorder(root);
            order[strlen(order)-1]='\n';
            printf(order);
        }
        if(!strcmp(word, "PREFIXA")){
            strcpy(order, "");
            preorder(root);
            order[strlen(order)-1]='\n';
            printf(order);
        }
        if(!strcmp(word, "POSFIXA")){
            strcpy(order, "");
            posorder(root);
            order[strlen(order)-1]='\n';
            printf(order);
        }
    }
    return 0;
}
