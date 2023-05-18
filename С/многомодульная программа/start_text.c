#include <stdio.h>
#include <string.h>
#include "rules.h"
#define N 101

int check(char str[], int n)
{
    int i = 0;
    while (str[i] != 0 && i < n)
    {
        if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
            return 2;
        i++;
    }
    return 1;
}

void input(char str[], int *n)
{
    char c;
    int i = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        str[i] = c;
        i++;
    }
    (*n) = i;
}

void output(char str[], int n)
{   
    int i = 0;
    while (str[i] != 0 && i < n)
    {
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
}

int main()
{
    char str[N];
    int n = 0;
    printf("Введите входную строку\n");
    input (str, &n);
    printf("Ваша строка: ");
    output(str, n);
    printf("Ваше правило обработки -  %d\n", check(str, n));
    if (check(str, n) == 1)
    {
        printf("Заменить каждую ненулевую цифру на соответствующую ей по порядковому номеру строчную букву латинского алфавита (1 → a, 2 → b и т.д.)\n");
        rule_one(str, n);
    }
    else
    {
        printf("Удалить из текста все повторные вхождения его первого символа\n");
        rule_two(str, n);
    }
    printf("Ваша новая обработанная строка: ");
    output(str, n);
    printf("\n");
    return 0;
}