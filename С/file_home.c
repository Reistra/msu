#include <stdio.h>
#include <stdlib.h>

FILE *file1, *file2;

struct node {
    int elem;
    struct node* next;
}; 


void rewrite(FILE *from, FILE *to) {
    int i = 1; int c;

    fprintf(to, "%d ", i);
    while ((c = fgetc(from)) != EOF) {
        fputc(c, to);
        if (c == '\n') 
            fprintf(to, "%d ", ++i);
    }
}

void del_space(FILE *from, FILE *to) {
    int c, last = '\n';
    c = getc(from);

    while (c != EOF) {
        if (c == '\n' && last == '\n') {
            last = c;
            c = fgetc(from);
        }
        fputc(c, to);
        last = c;
        c = getc(from);
    }
}

struct node* create_list(FILE *from) {              // выводит аски-коды
    int c; struct node *L = NULL, *last;
    while ((c = fgetc(from)) != EOF) {
        if (c != '\n') {
            if (!L) {
                L = malloc(sizeof(struct node));
                L->elem = c;
                L->next = NULL;
                last = L;
            }
            else {
                last->next = malloc(sizeof(struct node));
                last = last->next;
                last->elem = c;
                last->next = NULL;
            }
        }
        while (c != '\n' && c != EOF)           // мы уже внесли в список первый символ, далее перебираем элементы вплоть до конца строчки
            c = fgetc(from);
    }
    return L;
}

struct node * ccreate_list(FILE * f) {      //то, что ты делал на паре
    struct node *L = NULL, *last;
    int c;

    while ((c = fgetc(f)) != EOF) {
        if (c != '\n') {
            if (!L) {
                L = malloc(sizeof(struct node));
                L -> elem = c;
                L -> next = NULL;
                last = L;
            } else {
                last -> next = malloc(sizeof(struct node));
                last = last -> next;
                last -> elem = c;
                last -> next = NULL;
            }
        }

        while (c != '\n' && c != EOF) 
            c = fgetc(f);
    }

    return L;
}

void print_list (struct node *L) {
    while (L) {
        printf ("%c ", L->elem);
        printf ("*");
        L = L->next;    
    }
    printf("\n");
}

int main(int argc, char** argv) {
    struct node *list;
    
    if (argc != 3) {
        fprintf (stderr, "Invalid number of parametrs\n");
        return -1;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "w");

    //rewrite(file1, file2);
    del_space(file1, file2);
    list = ccreate_list(file1);
    print_list (list);
    return 0;
}