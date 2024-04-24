/*//==============================================================================================================
Необходимо составить программу qsstack.c, осуществляющую сортировку массива целых чисел в порядке возрастания.

В программе должен быть реализован нерекурсивный алгоритм быстрой сортировки, использующий в своей работе стек
заданий. Каждое задание описывает координаты подмассива, который нужно отсортировать, и представляет собой структуру

struct Task {
    int low, high;
};
Программа должна считывать со стандартного потока ввода размер массива n и значения элементов массива. 
В стандартный поток вывода должны выводиться элементы отсортированного массива.
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct Task {
    int low, high;
};

struct Stack {
    struct Task *data;
    int capacity;
    int top;
};

bool empty(struct Stack s) {
    return 0 == s.top;
}

void push(struct Stack *stack, struct Task element) {
    stack->data[stack->top] = element;
    ++stack->top;
}

struct Task pop(struct Stack *s) {
    if (empty(s[0])) {
        printf("ERROR: underflow");
    } else {
        --s->top;
        return s->data[s->top];
    }
}

void stack_init(struct Stack *s, int n) {
    s->data = (struct Task *) malloc(sizeof(struct Task) * n);
    s->capacity = n;
    s->top = 0;
}

void int_swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *a, int l, int r) {
    int i = l;
    for (int j = l; j < r; ++j) {
        if (a[j] < a[r]) {
            int_swap(&a[i], &a[j]);
            ++i;
        }
    }
    int_swap(&a[i], &a[r]);
    return i;
}

void quick_sort(int *a, int l_input, int r_input) {
    int l, r;
    struct Task CurrentTask;
    struct Stack s;
    CurrentTask.low = l_input;
    CurrentTask.high = r_input;
    stack_init(&s, r_input + 1);
    push(&s, CurrentTask);
    while (!empty(s)) {
        CurrentTask = pop(&s);
        l = CurrentTask.low;
        r = CurrentTask.high;
        if (r <= l) {
            continue;
        }
        int i = partition(a, l, r);
        struct Task task;
        if (i - l > r - i) {
            task.high = i - 1;
            task.low = l;
            push(&s, task);
            task.low = i + 1;
            task.high = r;
            push(&s, task);
        } else {
            task.high = r;
            task.low = i + 1;
            push(&s, task);
            task.low = l;
            task.high = i - 1;
            push(&s, task);
        }
    }
    free(s.data);
}

int main() {
    int number_of_numbers;
    scanf("%d", &number_of_numbers);
    int *arr_of_numbers = malloc((number_of_numbers + 1) * sizeof(int));
    for (int i = 0; i < number_of_numbers; ++i) {
        scanf("%d", &arr_of_numbers[i]);
    }
    quick_sort(arr_of_numbers, 0, number_of_numbers - 1);
    for (int i = 0; i < number_of_numbers; ++i) {
        printf("%d ", arr_of_numbers[i]);
    }
    free(arr_of_numbers);
    return 0;
}
