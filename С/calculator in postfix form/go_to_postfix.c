#include <stdio.h>
#define N 256


void push(int* stack, int* num, int symbol)
{
    stack[(*num)++] = symbol;
}

int pop(int* stack, int* num)
{
    return stack[--(*num)];
}

int stack_is_empty(int num)
{
    return !num;
}

int priority_of_symbols(int k){
    switch (k)
    {
        case '~':
            return 1;
        case '|':
            return 2;
        case '&':
            return 3;

        case '(':
            return -1;
        case ')':
            return -2;

        default:
            return 0; //если операнд, то 0
    }
}


int main(void)
{
    int stack[N];
    int top_of_stack = 0, symbol = 0, last = '|'; //не выдаем ошибку на первую скобку
    int output[N];

    int pointer = 0; //указатель на конец выходной строки (output)
    int counter = 0; //счётчик открытых, но ещё не закрытых скобок

    while (((symbol = getchar()) != '=') && (symbol != '\n') && (symbol != EOF)) //пока вводятся символы
    {
        if (symbol == ' ')
        {
            continue;
        }

        if (priority_of_symbols(symbol) > 0){
            while ((priority_of_symbols(stack[top_of_stack-1]) >= priority_of_symbols(symbol)) && (!stack_is_empty(top_of_stack)))
            {
                output[pointer] = ' ';
                pointer++;
                output[pointer] = pop(stack,&top_of_stack);
                pointer++;
            }
            push(stack,&top_of_stack,symbol);
            output[pointer] = ' ';
            pointer++;
        }

        if (symbol == '(')
        {
            if (!priority_of_symbols(last))
            {
                fprintf(stderr,"Idi nahuix1"); 
                return -1; // если выполнилось, то просто скипаем дальнейшие действия и прерываем программу нахуй
            }
            counter++;
            push(stack,&top_of_stack,symbol);
        }

        // что-то срочно надо выдумать такое, чтобы код заработаааал

        if (symbol == ')')
        {
            if (counter == 0)
            {
                fprintf(stderr,"Idi nahuiх2"); // если выполнилось, то просто скипаем дальнейшие действия и прерываем программу нахуй х2
                return -1;
            }
            else
            {
            while (stack[top_of_stack-1] != '(')
            {
                output[pointer] = ' ';
                pointer++;
                output[pointer] = pop(stack,&top_of_stack);
                pointer++;
            }
            counter--;
            pop(stack,&top_of_stack);
            }
        }

        if (!priority_of_symbols(symbol)) // если операнд  (не 0 -> 1)
        {
            output[pointer] = symbol;
            pointer++;
        }
        last = symbol;
    }

    if (counter!=0){
        fprintf(stderr,"Idi nahuiх3"); //если выполнилось, то просто скипаем дальнейшие действия и прерываем программу нахуй
        return -1;
    }

    while (top_of_stack>0){
        output[pointer] = ' ';
        pointer++;
        output[pointer] = pop(stack, &top_of_stack);
        pointer++;
    }

    for (int i=0 ; i < pointer ; i++){
        printf("%c", output[i]);
    }
    putchar('\n');
    return 0;
}
