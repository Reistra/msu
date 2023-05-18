#include <stdio.h>
#include <stdlib.h>

struct tree {
    int elem;
    struct tree *left;
    struct tree *right;
}; 


void add (struct tree **root, int x) {
    if (!(*root)) {
        (*root) = malloc(sizeof(struct tree));
        (*root)->elem = x;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else {
        if (x < (*root)->elem) 
            add (&((*root)->left), x);
        else 
            add (&((*root)->right), x);
    }
}

void print_tree (struct tree *root) {
    if (root != NULL) {
        printf ("%d ", root->elem);
        print_tree (root->left);
        print_tree (root->right);
    }
}

struct tree* copy_tree (struct tree *root) {
    struct tree *L = NULL;
    if (root == NULL) {
        return NULL;
    }
    else {
        L = malloc(sizeof(struct tree));
        L->elem = root->elem;
        L->left = NULL;
        L->right = NULL; 
        L->left = copy_tree(root->left);
        L->right = copy_tree(root->right);
    }
    return L;
}

int height (struct tree *root) {
    if (root == NULL) return 0;
    else {
        int l = height(root->left);
        int r = height(root->right);
        if (l >= r) return 1 + l;
        else return 1 + r;
    }
}

int check (struct tree *root) {
    if (root == NULL) return 1;
    else 
        return (abs(height(root->left) - height(root->right)) <= 1) * (check(root->right)) * (check(root->left));
}

int same(struct tree *T1, struct tree *T2) {
    if (!T1 && !T2) 
        return 1;
    else {
        if (T1->elem != T1->elem || (T1 && !T2) || (!T1 && T2)); 
            return 0;
        same (T1->left, T2->left);
        same (T1->right, T2->right);
    }
}

int main () {
    int x; struct tree *T = NULL, *L = NULL; 
    for (int i = 0; i < 5; i++) {
        scanf("%d", &x);
        add (&T, x);
    }
    // print_tree (T);
    // L = copy_tree (T);
    for (int i = 0; i < 5; i++) {
        scanf("%d", &x);
        add (&L, x);
    }
    printf("\n");
    //print_tree (L);
    printf ("\n");
    printf ("%d\n", height(T));
    printf("are the tha same? %d\n", same(T, L));
    return 0;
}