#include <stdio.h>
#include <stdlib.h>

struct list {
    int elem;
    struct list* next;
};

struct list* create(void) {
    int x;
    struct list* L = NULL, *p = NULL;
    while ((x = getchar()) != '\n') {
        if (L == NULL) {                        //в случае если список пустой
            L = malloc(sizeof(struct list));
            L->elem = x;
            L->next = NULL;
            p = L;
        }
        else {
            p->next = malloc(sizeof(struct list));
            p = p -> next;
            p->elem = x;
            p->next = NULL;
        }
    }
    return L;
}

struct list* rcreate(void) {
    int x;
    struct list* L = NULL;
    if (scanf("%d", &x) != 1) {
        return NULL;
    }
    else {
        L = malloc(sizeof(struct list));
        L->elem = x;
        L->next = rcreate();
        return L;
    }
}

void print_list (struct list *L) {
    while (L) {
        printf ("%d ", L->elem);
        L = L->next;
    }
    printf("\n");
}

double average(struct list *L) {
    double sr = 0; double k = 0;
    while (L) {
        sr += L->elem;
        k++;
        L = L->next;
    }
    return sr/k;
}

void rdelete_last (struct list **L) {
    if (*L == NULL) 
        return;
    else if ((*L)->next == NULL) {
        free (*L);
        (*L) = NULL;
    }
    else 
        rdelete_last (&(*L)->next);
}

void isordering(struct list **L) {

}

struct list* create_new_in_order(struct list *L1, struct list *L2) {
    struct list *N = NULL, *p;
    if (!L1 && !L2) {
        return NULL;
    }
    else {
        N = malloc(sizeof(struct list));
        p = N;
        while (L1 || L2) {
            if (L1 && L2) {
                if (L1->elem < L2->elem) {
                    N->elem = L1->elem;
                        // printf("*%d ",L1->elem);
                    N->next = malloc(sizeof(struct list));
                    N = N->next;
                    L1 = L1->next;
                }
                else {
                    N = malloc(sizeof(struct list));
                    N->elem = L2->elem;
                        // printf("*%d ",L2->elem);
                    N->next = malloc(sizeof(struct list));
                    N = N->next;
                    L2 = L2->next;
                }
            }
        
        else if (!L2) {
            while (L1) {
                N->elem = L1->elem;
                    // printf("*%d ",N->elem);
                N->next = malloc(sizeof(struct list));
                N = N->next;
                L1 = L1->next;
            }
        }
        else if (!L1) {
            while (L2) {
                N = malloc(sizeof(struct list));
                N->elem = L2->elem;
                    // printf("*%d ",N->elem);
                N->next = malloc(sizeof(struct list));
                N = N->next;
                L2 = L2->next;
            }
        }
        }
    }
    return p;
}

void rdelete_list(struct list **L) {
    if (*L == NULL)
        return;
    rdelete_list(&(*L)->next);
    free(*L);
    *L = NULL;
}


int main () {
    struct list *L, *R, *N;
    L = create();
    R = create();
    //print_list(L);
    //printf ("average meaning = %.3f\n", average(L));
    //rdelete_last(&L);
    //print_list(L);
    N = create_new_in_order(L, R);
    print_list(N);
    rdelete_list(&L);
    return 0;
}