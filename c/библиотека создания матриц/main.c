#include <stdio.h>
#include "matrix.h"

main () {
    int n = 2; int m = 4; int** mas; 
    generate (mas, n, m);
    printf ("кол-во строк - %d, кол-во столбцов -  %d", n, m);
    input (mas, n, m);
    printf ("\n");
    output (mas, n, m);
    delete (mas, n, m);
    return 0;
}