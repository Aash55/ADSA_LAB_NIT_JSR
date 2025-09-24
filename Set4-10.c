#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------ AVL TREE (full) ------------------ */
typedef struct AVLNode { int k,h; struct AVLNode *l,*r; } AVLNode;
typedef struct { AVLNode *root; } AVLTree;
static int ah(AVLNode *n){ return n? n->h:0; }
static int max2(int a,int b){ return a>b?a:b; }
static AVLNode* anew(int k){ AVLNode *n=malloc(sizeof* n); n->k=k; n->l=n->r=NULL; n->h=1; return n; }
static AVLNode* rotR(AVLNode *y){ AVLNode *x=y->l; y->l=x->r; x->r=y; y->h=1+max2(ah(y->l),ah(y->r)); x->h=1+max2(ah(x->l),ah(x->r)); return x; }
static AVLNode* rotL(AVLNode *x){ AVLNode *y=x->r; x->r=y->l; y->l=x; x->h=1+max2(ah(x->l),ah(x->r)); y->h=1+max2(ah(y->l),ah(y->r)); return y; }
static int bf(AVLNode *n){ return n?ah(n->l)-ah(n->r):0; }
static AVLNode* avl_insert(AVLNode *n,int k){
    if(!n) return anew(k);
    if(k<n->k) n->l=avl_insert(n->l,k);
    else if(k>n->k) n->r=avl_insert(n->r,k);
    else return n;
    n->h=1+max2(ah(n->l),ah(n->r));
    int b=bf(n);
    if(b>1 && k<n->l->k) return rotR(n);
    if(b<-1 && k>n->r->k) return rotL(n);
    if(b>1 && k>n->l->k){ n->l=rotL(n->l); return rotR(n); }
    if(b<-1 && k<n->r->k){ n->r=rotR(n->r); return rotL(n); }
    return n;
}
static AVLNode* minAVL(AVLNode *n){ while(n->l) n=n->l; return n; }
static AVLNode* avl_delete(AVLNode *r,int k){
    if(!r) return r;
    if(k<r->k) r->l=avl_delete(r->l,k);
    else if(k>r->k) r->r=avl_delete(r->r,k);
    else {
        if(!r->l||!r->r){ AVLNode *t=r->l?r->l:r->r; if(!t){ free(r); return NULL;} *r=*t; free(t);}
        else { AVLNode *t=minAVL(r->r); r->k=t->k; r->r=avl_delete(r->r,t->k);}
    }
    r->h=1+max2(ah(r->l),ah(r->r));
    int b=bf(r);
    if(b>1 && bf(r->l)>=0) return rotR(r);
    if(b>1 && bf(r->l)<0){ r->l=rotL(r->l); return rotR(r);}
    if(b<-1 && bf(r->r)<=0) return rotL(r);
    if(b<-1 && bf(r->r)>0){ r->r=rotR(r->r); return rotL(r);}
    return r;
}
static AVLNode* avl_search(AVLNode *r,int k){ while(r){ if(k==r->k) return r; r=k<r->k?r->l:r->r; } return NULL; }
static void avl_free(AVLNode *n){ if(!n) return; avl_free(n->l); avl_free(n->r); free(n); }

/* ------------------ RB / B-Tree / B+Tree (study stubs) ------------------ */
typedef struct RBNode { int k; struct RBNode *l,*r; } RBNode;
typedef struct { RBNode *root; } RBTree;
static RBNode* rb_new(int k){ RBNode* n=malloc(sizeof*n); n->k=k; n->l=n->r=NULL; return n;}
static RBNode* rb_insert(RBNode *r,int k){ if(!r) return rb_new(k); if(k<r->k) r->l=rb_insert(r->l,k); else if(k>r->k) r->r=rb_insert(r->r,k); return r;}
static RBNode* rb_search(RBNode *r,int k){ while(r){ if(k==r->k) return r; r=k<r->k?r->l:r->r; } return NULL;}
static void rb_free(RBNode *r){ if(!r) return; rb_free(r->l); rb_free(r->r); free(r); }

typedef struct BNode { int n; int keys[4]; } BNode; /* super simplified */
typedef struct { BNode *root; } BTree;

typedef struct BPNode { int n; int keys[4]; } BPNode; /* super simplified */
typedef struct { BPNode *root; } BPtree;

/* ------------------ Unified Tree Interface ------------------ */
enum {TYPE_AVL=1, TYPE_RB, TYPE_BT, TYPE_BPT};

typedef struct {
    int type;
    void *impl;
} Tree;

/* Factory */
Tree* createTree(int type){
    Tree *t=malloc(sizeof* t); t->type=type;
    if(type==TYPE_AVL){ AVLTree *x=malloc(sizeof* x); x->root=NULL; t->impl=x;}
    else if(type==TYPE_RB){ RBTree *x=malloc(sizeof* x); x->root=NULL; t->impl=x;}
    else if(type==TYPE_BT){ BTree *x=malloc(sizeof* x); x->root=malloc(sizeof* x->root); x->root->n=0; t->impl=x;}
    else { BPtree *x=malloc(sizeof* x); x->root=malloc(sizeof* x->root); x->root->n=0; t->impl=x;}
    return t;
}
void deleteTree(Tree* t){
    if(!t) return;
    if(t->type==TYPE_AVL){ AVLTree* x=t->impl; avl_free(x->root); free(x);}
    else if(t->type==TYPE_RB){ RBTree* x=t->impl; rb_free(x->root); free(x);}
    else free(t->impl);
    free(t);
}
void insertItem(Tree* t,int k){
    if(t->type==TYPE_AVL){ AVLTree* x=t->impl; x->root=avl_insert(x->root,k);}
    else if(t->type==TYPE_RB){ RBTree* x=t->impl; x->root=rb_insert(x->root,k);}
    else if(t->type==TYPE_BT){ BTree* x=t->impl; if(x->root->n<4) x->root->keys[x->root->n++]=k;}
    else { BPtree* x=t->impl; if(x->root->n<4) x->root->keys[x->root->n++]=k;}
}
void deleteItem(Tree* t,int k){
    if(t->type==TYPE_AVL){ AVLTree* x=t->impl; x->root=avl_delete(x->root,k);}
    else if(t->type==TYPE_RB){ /* stub */ }
    else { /* stub */ }
}
void* serachItem(Tree* t,int k){
    if(t->type==TYPE_AVL){ AVLTree* x=t->impl; return avl_search(x->root,k);}
    else if(t->type==TYPE_RB){ RBTree* x=t->impl; return rb_search(x->root,k);}
    else if(t->type==TYPE_BT){ BTree* x=t->impl; for(int i=0;i<x->root->n;i++) if(x->root->keys[i]==k) return x->root; }
    else { BPtree* x=t->impl; for(int i=0;i<x->root->n;i++) if(x->root->keys[i]==k) return x->root; }
    return NULL;
}

/* ------------------ Menu-driven main ------------------ */
int main(){
    int choice;
    printf("Choose Tree Type:\n1. AVL\n2. Red-Black (stub)\n3. B-Tree (stub)\n4. B+Tree (stub)\n> ");
    scanf("%d",&choice);
    Tree *t=createTree(choice);

    while(1){
        printf("\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. Exit\n> ");
        int op; scanf("%d",&op);
        if(op==1){ int k; printf("Key: "); scanf("%d",&k); insertItem(t,k);}
        else if(op==2){ int k; printf("Key: "); scanf("%d",&k); deleteItem(t,k);}
        else if(op==3){ int k; printf("Key: "); scanf("%d",&k); printf("%s\n",serachItem(t,k)?"Found":"Not Found");}
        else break;
    }

    deleteTree(t);
    return 0;
}