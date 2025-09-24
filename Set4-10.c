#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------ AVL Tree ------------------ */

// AVL Node structure
typedef struct AVLNode {
    int k, h;
    struct AVLNode *l, *r;
} AVLNode;

// AVL Tree structure
typedef struct {
    AVLNode *root;
} AVLTree;

// Helper function to get the height of a node
static int ah(AVLNode *n) {
    return n ? n->h : 0;
}

// Helper function to find the maximum of two integers
static int max2(int a, int b) {
    return a > b ? a : b;
}

// Function to create a new AVL node
static AVLNode *anew(int k) {
    AVLNode *n = malloc(sizeof(*n));
    if (n) {
        n->k = k;
        n->l = n->r = NULL;
        n->h = 1;
    }
    return n;
}

// Right rotation
static AVLNode *rotR(AVLNode *y) {
    AVLNode *x = y->l;
    y->l = x->r;
    x->r = y;
    y->h = 1 + max2(ah(y->l), ah(y->r));
    x->h = 1 + max2(ah(x->l), ah(x->r));
    return x;
}

// Left rotation
static AVLNode *rotL(AVLNode *x) {
    AVLNode *y = x->r;
    x->r = y->l;
    y->l = x;
    x->h = 1 + max2(ah(x->l), ah(x->r));
    y->h = 1 + max2(ah(y->l), ah(y->r));
    return y;
}

// Get balance factor of node n
static int bf(AVLNode *n) {
    return n ? ah(n->l) - ah(n->r) : 0;
}

// Insert a key into the AVL tree
static AVLNode *avl_insert(AVLNode *n, int k) {
    if (!n)
        return anew(k);
    if (k < n->k)
        n->l = avl_insert(n->l, k);
    else if (k > n->k)
        n->r = avl_insert(n->r, k);
    else
        return n; // Key already exists

    n->h = 1 + max2(ah(n->l), ah(n->r));
    int b = bf(n);

    // Left Left Case
    if (b > 1 && k < n->l->k)
        return rotR(n);
    // Right Right Case
    if (b < -1 && k > n->r->k)
        return rotL(n);
    // Left Right Case
    if (b > 1 && k > n->l->k) {
        n->l = rotL(n->l);
        return rotR(n);
    }
    // Right Left Case
    if (b < -1 && k < n->r->k) {
        n->r = rotR(n->r);
        return rotL(n);
    }
    return n;
}

// Find the node with the minimum key value in an AVL tree
static AVLNode *minAVL(AVLNode *n) {
    while (n->l)
        n = n->l;
    return n;
}

// Delete a key from the AVL tree
static AVLNode *avl_delete(AVLNode *r, int k) {
    if (!r)
        return r;
    if (k < r->k)
        r->l = avl_delete(r->l, k);
    else if (k > r->k)
        r->r = avl_delete(r->r, k);
    else {
        // Node with only one child or no child
        if (!r->l || !r->r) {
            AVLNode *t = r->l ? r->l : r->r;
            if (!t) {
                free(r);
                return NULL;
            }
            *r = *t;
            free(t);
        } else {
            // Node with two children: Get the inorder successor
            AVLNode *t = minAVL(r->r);
            r->k = t->k;
            r->r = avl_delete(r->r, t->k);
        }
    }
    if (!r)
        return r;

    r->h = 1 + max2(ah(r->l), ah(r->r));
    int b = bf(r);

    // Left Left Case
    if (b > 1 && bf(r->l) >= 0)
        return rotR(r);
    // Left Right Case
    if (b > 1 && bf(r->l) < 0) {
        r->l = rotL(r->l);
        return rotR(r);
    }
    // Right Right Case
    if (b < -1 && bf(r->r) <= 0)
        return rotL(r);
    // Right Left Case
    if (b < -1 && bf(r->r) > 0) {
        r->r = rotR(r->r);
        return rotL(r);
    }
    return r;
}

// Search for a key in the AVL tree
static AVLNode *avl_search(AVLNode *r, int k) {
    while (r) {
        if (k == r->k)
            return r;
        r = k < r->k ? r->l : r->r;
    }
    return NULL;
}

// Free all nodes in the AVL tree
static void avl_free(AVLNode *n) {
    if (!n)
        return;
    avl_free(n->l);
    avl_free(n->r);
    free(n);
}

/* ------------------ Red-Black / B-Tree / B+Tree (stubs) ------------------ */

// Red-Black Node structure
typedef struct RBNode {
    int k;
    struct RBNode *l, *r;
} RBNode;

// Red-Black Tree structure
typedef struct {
    RBNode *root;
} RBTree;

// Function to create a new RB node
static RBNode *rb_new(int k) {
    RBNode *n = malloc(sizeof(*n));
    if (n) {
        n->k = k;
        n->l = n->r = NULL;
    }
    return n;
}

// Insert a key into the Red-Black Tree
static RBNode *rb_insert(RBNode *r, int k) {
    if (!r)
        return rb_new(k);
    if (k < r->k)
        r->l = rb_insert(r->l, k);
    else if (k > r->k)
        r->r = rb_insert(r->r, k);
    return r;
}

// Search for a key in the Red-Black Tree
static RBNode *rb_search(RBNode *r, int k) {
    while (r) {
        if (k == r->k)
            return r;
        r = k < r->k ? r->l : r->r;
    }
    return NULL;
}

// Free all nodes in the Red-Black Tree
static void rb_free(RBNode *r) {
    if (!r)
        return;
    rb_free(r->l);
    rb_free(r->r);
    free(r);
}

// B-Tree Node structure (super simplified)
typedef struct BNode {
    int n;
    int keys[4];
} BNode;

// B-Tree structure
typedef struct {
    BNode *root;
} BTree;

// B+Tree Node structure (super simplified)
typedef struct BPNode {
    int n;
    int keys[4];
} BPNode;

// B+Tree structure
typedef struct {
    BPNode *root;
} BPtree;

/* ------------------ Unified Tree Interface ------------------ */

// Enum for tree types
enum {
    TYPE_AVL = 1,
    TYPE_RB,
    TYPE_BT,
    TYPE_BPT
};

// Unified Tree structure
typedef struct {
    int type;
    void *impl;
} Tree;

// Factory function to create a new tree
Tree *createTree(int type) {
    Tree *t = malloc(sizeof(*t));
    if (!t)
        return NULL;
    t->type = type;

    if (type == TYPE_AVL) {
        AVLTree *x = malloc(sizeof(*x));
        if (x) {
            x->root = NULL;
            t->impl = x;
        } else {
            free(t);
            return NULL;
        }
    } else if (type == TYPE_RB) {
        RBTree *x = malloc(sizeof(*x));
        if (x) {
            x->root = NULL;
            t->impl = x;
        } else {
            free(t);
            return NULL;
        }
    } else if (type == TYPE_BT) {
        BTree *x = malloc(sizeof(*x));
        if (x) {
            x->root = malloc(sizeof(*x->root));
            if (x->root) {
                x->root->n = 0;
                t->impl = x;
            } else {
                free(x);
                free(t);
                return NULL;
            }
        } else {
            free(t);
            return NULL;
        }
    } else { // TYPE_BPT
        BPtree *x = malloc(sizeof(*x));
        if (x) {
            x->root = malloc(sizeof(*x->root));
            if (x->root) {
                x->root->n = 0;
                t->impl = x;
            } else {
                free(x);
                free(t);
                return NULL;
            }
        } else {
            free(t);
            return NULL;
        }
    }
    return t;
}

// Function to free a tree
void deleteTree(Tree *t) {
    if (!t)
        return;
    if (t->type == TYPE_AVL) {
        AVLTree *x = t->impl;
        avl_free(x->root);
        free(x);
    } else if (t->type == TYPE_RB) {
        RBTree *x = t->impl;
        rb_free(x->root);
        free(x);
    } else {
        free(t->impl);
    }
    free(t);
}

// Function to insert an item into a tree
void insertItem(Tree *t, int k) {
    if (!t)
        return;
    if (t->type == TYPE_AVL) {
        AVLTree *x = t->impl;
        x->root = avl_insert(x->root, k);
    } else if (t->type == TYPE_RB) {
        RBTree *x = t->impl;
        x->root = rb_insert(x->root, k);
    } else if (t->type == TYPE_BT) {
        BTree *x = t->impl;
        if (x->root->n < 4)
            x->root->keys[x->root->n++] = k;
    } else { // TYPE_BPT
        BPtree *x = t->impl;
        if (x->root->n < 4)
            x->root->keys[x->root->n++] = k;
    }
}

// Function to delete an item from a tree
void deleteItem(Tree *t, int k) {
    if (!t)
        return;
    if (t->type == TYPE_AVL) {
        AVLTree *x = t->impl;
        x->root = avl_delete(x->root, k);
    } else if (t->type == TYPE_RB) {
        /* stub */
    } else {
        /* stub */
    }
}

// Function to search for an item in a tree
void *serachItem(Tree *t, int k) {
    if (!t)
        return NULL;
    if (t->type == TYPE_AVL) {
        AVLTree *x = t->impl;
        return avl_search(x->root, k);
    } else if (t->type == TYPE_RB) {
        RBTree *x = t->impl;
        return rb_search(x->root, k);
    } else if (t->type == TYPE_BT) {
        BTree *x = t->impl;
        for (int i = 0; i < x->root->n; i++)
            if (x->root->keys[i] == k)
                return x->root;
    } else { // TYPE_BPT
        BPtree *x = t->impl;
        for (int i = 0; i < x->root->n; i++)
            if (x->root->keys[i] == k)
                return x->root;
    }
    return NULL;
}

/* ------------------ Menu-driven Main Function ------------------ */

int main() {
    int choice;
    printf("Choose Tree Type:\n1. AVL\n2. Red-Black (stub)\n3. B-Tree (stub)\n4. B+Tree (stub)\n> ");
    scanf("%d", &choice);

    Tree *t = createTree(choice);
    if (!t) {
        printf("Failed to create tree.\n");
        return 1;
    }

    while (1) {
        printf("\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. Exit\n> ");
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int k;
            printf("Key: ");
            scanf("%d", &k);
            insertItem(t, k);
        } else if (op == 2) {
            int k;
            printf("Key: ");
            scanf("%d", &k);
            deleteItem(t, k);
        } else if (op == 3) {
            int k;
            printf("Key: ");
            scanf("%d", &k);
            printf("%s\n", serachItem(t, k) ? "Found" : "Not Found");
        } else {
            break;
        }
    }

    deleteTree(t);
    return 0;
}