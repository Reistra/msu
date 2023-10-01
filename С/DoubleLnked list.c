#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char *elem;
    struct list *prev;
    struct list *next;
} list;

list* create_list(char *elem) {
    list *p = (list*)malloc(sizeof(list));
    p->elem = (char*)malloc(strlen(elem) + 1);
    strcpy(p->elem, elem);
    p->prev = NULL;
    p->next = NULL;
    return p;
}

void delete_node(list *L) {
    if (L != NULL) {
        free(L->elem);
        free(L);
    }
}

void print_list(list *L) {
    list *cur = L;
    while (cur != NULL) {
        printf("%s ", cur->elem);
        cur = cur->next;
    }
    printf("\n");
}

void delete_indexList(list **L, int index) {
    if (*L == NULL) {
        return;
    }
    
    list *cur = *L;
    int i = 0;
    
    while (cur != NULL && i < index) {
        cur = cur->next;
        i++;
    }
    
    if (cur == NULL) {
        return;
    }
    
    if (cur->prev != NULL) {
        cur->prev->next = cur->next;
    }
    
    if (cur->next != NULL) {
        cur->next->prev = cur->prev;
    }
    
    if (*L == cur) {
        *L = cur->next;
    }
    
    delete_node(cur);
}

void insert_afterIndex(list** L, int index, char *elem) {
    if (*L == NULL) {
        return;
    }
    
    list *cur = *L;
    int i = 0;
    
    while (cur != NULL && i < index) {
        cur = cur->next;
        i++;
    }
    
    if (cur == NULL) {
        return;
    }
    
    list *newlist = create_list(elem);
    
    newlist->prev = cur;
    newlist->next = cur->next;
    
    if (cur->next != NULL) {
        cur->next->prev = newlist;
    }
    
    cur->next = newlist;
}

void delete_list(list **L) {
    list *cur = *L;
    
    while (cur != NULL) {
        list *temp = cur;
        cur = cur->next;
        delete_node(temp);
    }
    
    *L = NULL;
}

int main() {
    list *L = NULL;
    
    int choice = 0, n; char c[100];

        printf("Enter number of elements\n");
        scanf("%d", &n);

        printf("Enter elements\n");
        scanf("%s", &c);

        L = create_list(c);

        for (int i = 0; i < n-1; i++) {
            scanf("%s", &c);
            insert_afterIndex(&L, i, c);
        }

        print_list(L);

    while (1) {

        printf("1. Insert node after Index\n2. Delete node after Index\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int index;
            printf("Enter index (from 0 to n-1): ");
            scanf("%d", &index);

            if (index < 0 || index > n-1) {
                printf("Invalid index\n");
                continue;
            }

            printf("Enter elem: ");
            scanf("%s", c);
            insert_afterIndex(&L, index, c);
            print_list(L);
            n++;
        }
        else if (choice == 2) {
            int index;
            printf("Enter index (from 0 to n-1): ");
            scanf("%d", &index);

            if (index < 0 || index > n-1) {
                printf("Invalid index\n");
                continue;
            }

            delete_indexList(&L, index);
            print_list(L);
            n--;
        }
        
        else if (choice == 3) {
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }
    
    delete_list(&L);
    
    return 0;
}