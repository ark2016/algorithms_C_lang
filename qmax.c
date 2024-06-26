/*//==============================================================================================================
Реализуйте через двойной стек набор операций InitQueue, Enqueue, Dequeue, QueueEmpty и Maximum для работы с 
очередью целых чисел. Операция Maximum возвращает максимальное целое число, в данный момент времени находящееся 
в очереди. Операции Enqueue, QueueEmpty и Maximum должны работать за константное время, а операция Dequeue — за
амортизированное константное время.

Составьте программу qmax.c, демонстрирующую работоспособность реализованных операций.

Формат входных данных. Первая строка, считываемая со стандартного потока ввода, содержит общее количество 
выполняемых операций n (0 <= n <= 100 000). Каждая из следующих n строк содержит описание операции.

Операция либо имеет форму ENQ x (добавить число x в хвост очереди, -2 000 000 000 < x < 2 000 000 000), 
либо форму DEQ (удалить головной элемент из очереди), либо форму MAX (показать текущее максимальное число), 
либо форму EMPTY (проверить пустоту очереди).

Можно считать, что последовательность операций составлена правильно, то есть перед каждой операцией DEQ 
очередь не пуста.

Формат результата работы программы. Для каждой операции DEQ вывести в стандартный поток вывода значение удаляемого 
головного элемента очереди. Для каждой операции MAX вывести в стандартный поток вывода текущее максимальное число. 
Для каждой операции EMPTY вывести в стандартный поток вывода «true» или «false» в зависимости от того, пуста 
очередь или нет.

Подсказка. Как реализовать стек с операциями Push, Pop и Maximum за константное время?
*///==============================================================================================================
#include<stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include<string.h>
#include <limits.h>

#define SIZE_OF_STACK 1000001
#define DEFAULT_OPERATIONS 4

typedef struct Pair {
    int key;
    int value;
} Pair;

typedef struct DoubleStack {
    int cap;
    int top1;
    int top2;
    Pair *data;
} DoubleStack;

DoubleStack InitDoubleStack(int n);

int max(int a, int b);

bool isQueueEmpty(DoubleStack *s);

void push1(DoubleStack *s, int x);

void push2(DoubleStack *s, int x);

int maximum(DoubleStack *s);

int pop1(DoubleStack *s);

int pop2(DoubleStack *s);

void enqueue(DoubleStack *s, int x);

int dequeue(DoubleStack *s);

void freeStack(DoubleStack *stack);

int gettingOperationNumber(const char *operation);

DoubleStack getStack(const char *operation, int *x, DoubleStack *stack);

int main() {
    char operation[6];
    int x;
    DoubleStack stack;
    stack = InitDoubleStack(SIZE_OF_STACK);
    while (true) {
        scanf("%stack", operation);
        if (!strcmp(operation, "END")) {
            break;
        }
        stack = getStack(operation, &x, &stack);
    }
    freeStack(&stack);
    return 0;
}

DoubleStack InitDoubleStack(int n) {
    DoubleStack doubleStack;
    doubleStack.data = malloc(n * sizeof(Pair));
    doubleStack.cap = n;
    doubleStack.top1 = 0;
    doubleStack.top2 = n - 1;
    return doubleStack;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

bool isQueueEmpty(DoubleStack *s) {
    return !(s->top1) && (s->top2 == s->cap - 1);
}

void push1(DoubleStack *s, int x) {
    if (s->top1 > s->top2) {
        printf("ERROR: overflow\n");
    } else {
        s->data[s->top1].value = x;
        if (0 != s->top1) {
            s->data[s->top1].key = max(s->data[s->top1 - 1].key, x);
        } else {
            s->data[s->top1].key = x;
        }
        ++s->top1;
    }
}

void push2(DoubleStack *s, int x) {
    if (s->top2 < s->top1) {
        printf("ERROR: overflow\n");
    } else {
        s->data[s->top2].value = x;
        if (s->top2 != s->cap - 1) {
            s->data[s->top2].key = max(s->data[s->top2 + 1].key, x);
        } else {
            s->data[s->top2].key = x;
        }
        --s->top2;
    }
}

void enqueue(DoubleStack *s, int x) {
    push1(s, x);
}

int maximum(DoubleStack *s) {
    if (s->top1 == 0) {
        return s->data[s->top2 + 1].key;
    } else if (s->top2 == s->cap - 1) {
        return s->data[s->top1 - 1].key;
    } else {
        return max(s->data[s->top1 - 1].key, s->data[s->top2 + 1].key);
    }
}

int pop1(DoubleStack *s) {
    if (!s->top1) {
        printf("ERROR: devastation\n");
    }
    --s->top1;
    Pair x = s->data[s->top1];
    return x.value;
}

int pop2(DoubleStack *s) {
    if (s->top2 == s->cap - 1) {
        printf("ERROR: devastation\n");
    }
    ++s->top2;
    Pair x = s->data[s->top2];
    return x.value;
}

int dequeue(DoubleStack *s) {
    if (s->top2 == (s->cap - 1))
        while (s->top1)
            push2(s, pop1(s));
    int x = pop2(s);
    return x;
}

void freeStack(DoubleStack *stack) {
    free((*stack).data);
    (*stack).data = NULL;
}

int gettingOperationNumber(const char *operation) {
    const char *array_of_operation[] = {"ENQ", "DEQ", "MAX", "EMPTY"};
    for (int i = 0; i < DEFAULT_OPERATIONS; ++i) {
        if (!strcmp(operation, array_of_operation[i])) {
            return i;
        }
    }
    return -1;
}

DoubleStack getStack(const char *operation, int *x, DoubleStack *stack) {
    switch (gettingOperationNumber(operation)) {

        case 0:
            scanf("%d", x);
            enqueue(stack, (*x));
            break;
        case 1:
            printf("%d\n", dequeue(stack));
            break;
        case 2:
            if (isQueueEmpty(stack)) {
                printf("ERROR: MAX doesn't exist, you forget to enter a number\n");
            } else {
                printf("%d\n", maximum(stack));
            }
            break;
        case 3:
            printf("%s\n", isQueueEmpty(stack) ? "true" : "false");
            break;
        case -1:
            printf("ERROR: wrong input operation\n");
            break;
    }
    return (*stack);
}
