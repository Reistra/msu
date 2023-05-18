/*Написать функцию, которая на вход получает строку, состоящую только из малых латинских букв (и в конце строки '\0') и преобразует ее следующим образом:
- если буква отличается от следующей - она не изменяется.
- группу подряд идущих символов заменить двумя объектами char, в первом из которых записать количество символов (от 2 до 9 - символом-цифрой), во втором - сам символ; например, "aaaaabccc" --> '5' 'a' 'b' '3' 'c' */


#include <stdio.h>
#include <string.h>
#define N 100

char str[N] = "abbccc";
char str1[N] = "aaabbc";
char str2[N] = "kaaaaaat";

void transform (char* str) {
    int i = 0; int j = 1; int k = 1;
    while (str[j] != '\0') {
        if (str[i] != str[j]) 
            printf ("%c", str[i]);
        if (str[i] == str[j]) { //если новый символ такой же, как предыдущий
            while (str[i] == str[j]) {  //до тех пор, пока новый символ не станет иным
                j++;
                k++;
            }
            printf ("%c%c", k + '0', str[i]);
            k = 1;
            i = j - 1;
        }
        i++;
        j++;
    }
    if (str[i] != str[i-1]) 
        printf ("%c",str[i]);
    printf ("\n");
}

int main() {
    transform (str);
    transform (str1);
    transform (str2);
    return 0;
}