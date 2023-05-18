#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int key;
    struct tree *left, *right;
};

struct tree * create_tree()
{
    int c = getchar();
    int elem;
    struct tree * T = NULL;
    if ((c = getchar()) == ')') return NULL;
    ungetc(c, stdin);
    scanf("%d", &elem);
    T = malloc(sizeof(struct tree));
    T -> key = elem;
    T -> left = create_tree();
    T -> right = create_tree();
    c = getchar();
    return T;
}

struct tree * add_elem(struct tree * T, int elem)
{
    if (!T)
    {
        T = malloc(sizeof(struct tree));
        T->key = elem;
        T->left = NULL;
        T->right = NULL;
    }
    else
    {
        if (elem > T->key)
        {
            T->right = add_elem(T->right, elem);
        }
        else if (elem < T->key)
        {
            T->left = add_elem(T->left, elem);
        }
    }
    return T;
}

void del_tree(struct tree ** T)
{
    if (*T == NULL) return;
    del_tree((&(*T)->left));
    del_tree((&(*T)->right));
    free(*T);
    *T = NULL;
}

void print_tree(struct tree * T)
{
    if (T == NULL)
    {
        printf("()");
    }
    else
    {
        printf("(%d", T->key);
        print_tree(T->left);
        print_tree(T->right);
        putchar(')');
    }
}

int check(struct tree * T, struct tree * min, struct tree * max)
{
    if (T == NULL) return 1;
    if (min && (T->key < min->key) ) return 0;
    if (max && (T->key > max->key) ) return 0;
    else return check(T->left, min, T) && check(T->right, T, max);
}

struct tree * copy_tree(struct tree * T)
{
    struct tree * T1 = NULL;
    if (!T) return NULL;
    T1 = malloc(sizeof(struct tree));
    T1->key = T->key;
    T1->left = copy_tree(T->left);
    T1->right = copy_tree(T->right);
    return T1;
}

int high_of_tree(struct tree * T)
{
    int hl = 0, hr = 0;
    if (!T) return 0;
    hl = 1 + high_of_tree(T->left);
    hr = 1 + high_of_tree(T->right);
    if (hl > hr) return hl;
    else return hr;
}

int max_and_min(struct tree * T)
{
    struct tree *max = T, *min = T;
    while (min->left) min = min->left;
    while (max->right) max = max->right;
    return min->key + max->key;
} 

int main(void)
{
    struct tree * T = NULL, * T1 = NULL;
    T = create_tree();
    /*for (int i = 0; i < 5; i++)
        T = add_elem(T, i);*/
    if (check(T, NULL, NULL))
        printf("YES");
    else 
        printf("NO");
    printf("\n");
    T1 = copy_tree(T);
    print_tree(T1);
    printf("\n");
    printf("%d\n", high_of_tree(T));
    printf("%d\n", max_and_min(T));
    del_tree(&T);
    del_tree(&T1);
    return 0;
}