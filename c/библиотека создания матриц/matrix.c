#include <stdio.h>
#include <stdlib.h>

int** generate (int** mas, int n, int m) {
    for (int i = 0; i < n; i++){ 
        (int**)calloc(n, sizeof(int*));
        for (int j = 0; j < m; j++) 
            (int*)calloc(m, sizeof(int));
    }
    return mas;
}

void input (int** mas, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf ("%d", &mas[i][j]);
}

void output (int** mas, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf ("%d ", mas[i][j]);
    printf ("\n");
}

void delete (int** mas, int n, int m) {
    for (int i = 0; i < n; i++)
            free (mas[i]);
    free (mas);
}