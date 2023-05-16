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
