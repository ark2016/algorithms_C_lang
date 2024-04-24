/*//==============================================================================================================
Пусть стековая машина — это устройство для выполнения арифметических операций, использующее для хранения 
промежуточных результатов вычислений стек целых чисел. Подразумевается, что каждая операция берёт операнды из стека 
и оставляет на стеке результат.

Составьте программу stackmachine.c, моделирующую работу стековой машины.

Формат входных данных. Первая строка, считываемая со стандартного потока ввода, содержит общее количество 
выполняемых 
операций n (0 <= n <= 100 000). Каждая из следующих n строк содержит описание операции.

Стековая машина должна обеспечивать выполнение следующих операций:

CONST x — кладёт в стек число x (-1 000 000 000 < x < 1 000 000 000);
ADD — сложение (снимает со стека два операнда a и b и кладёт в стек их сумму);
SUB — вычитание (снимает со стека операнд a, затем снимает со стека операнд b, кладёт в стек a - b);
MUL — умножение (снимает со стека два операнда a и b и кладёт в стек их произведение);
DIV — деление (снимает со стека операнд a, затем снимает со стека операнд b, кладёт в стек результат 
целочисленного деления a на b);
MAX — максимум двух чисел (снимает со стека два операнда a и b и кладёт в стек max(a, b));
MIN — минимум двух чисел (снимает со стека два операнда a и b и кладёт в стек min(a, b));
NEG — меняет знак числа, находящегося на вершине стека;
DUP — кладёт в стек копию числа, находящегося на вершине стека;
SWAP — меняет местами два числа, находящиеся на вершине стека.
Можно считать, что последовательность операций составлена правильно, то есть перед вызовом каждой операции стек 
содержит нужное ей количество операндов, деление на ноль и переполнение не возникают, и, кроме того, в результате 
выполнения всех операций на стеке остаётся единственное число.

Формат результата работы программы. В стандартный поток вывода необходимо вывести число, оставшееся на вершине 
стека в результате выполнения последовательности операций.
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_OPERATIONS 10
struct Stack {
    int capacity;
    int top;
    int *data;
};

bool empty(struct Stack s) {
    return 0 == s.top;
}

void stackInit(struct Stack *s, int n) {
    s->data = (int *) malloc(sizeof(int) * n);
    s->capacity = n;
    s->top = 0;
}

int pop(struct Stack *s) {
    if (empty(*s)) {
        printf("ERROR: underflow");
    }
    --s->top;
    --s->capacity;
    return s->data[s->top];
}

void push(struct Stack *stack, int element) {
    ++stack->capacity;
    stack->data = (int *) realloc(stack->data, (unsigned int) (stack->capacity) * sizeof(int));
    stack->data[stack->top] = element;
    ++stack->top;
}

int gettingOperationNumber(char *operation) {
    const char *arrayOfOperation[] = {"CONST", "ADD", "SUB", "MUL", "DIV", "MAX", "MIN", "NEG", "DUP", "SWAP"};
    for (int i = 0; i < DEFAULT_OPERATIONS; ++i) {
        if (0 == strcmp(operation, arrayOfOperation[i])) {
            return i;
        }
    }
    return -1;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

struct Stack operationRecognition(struct Stack *stack, char *operation) {
    switch (gettingOperationNumber(operation)) {
        case -1:
            printf("ERROR: wrong input operation");
            break;
            int number;
        case 0:
            scanf("%d", &number);
            push(stack, number);
            break;
            int a;
        case 1:
            a = pop(stack);
            int b = pop(stack);
            push(stack, a + b);
            break;
        case 2:
            a = pop(stack);
            b = pop(stack);
            push(stack, a - b);
            break;
        case 3:
            a = pop(stack);
            b = pop(stack);
            push(stack, a * b);
            break;
        case 4:
            a = pop(stack);
            b = pop(stack);
            push(stack, a / b);
            break;
        case 5:
            a = pop(stack);
            b = pop(stack);
            push(stack, max(a, b));
            break;
        case 6:
            a = pop(stack);
            b = pop(stack);
            push(stack, min(a, b));
            break;
        case 7:
            number = pop(stack);
            push(stack, -number);
            break;
        case 8:
            number = pop(stack);
            push(stack, number);
            push(stack, number);
            break;
        case 9:
            a = pop(stack);
            b = pop(stack);
            push(stack, a);
            push(stack, b);
            break;
    }
    return (*stack);
}

void freeStack(struct Stack *stack) {
    free((*stack).data);
    (*stack).data = NULL;
}

int main() {
    struct Stack stack;
    char operation[6];
    stackInit(&stack, 0);
    while (true) {
        scanf("%s", operation);
        if (0 == strcmp("END", operation)) {
            break;
        }
        stack = operationRecognition(&stack, operation);
    }
    printf("%d\n", stack.data[0]);
    freeStack(&stack);
    return 0;
}
