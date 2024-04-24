/*//==============================================================================================================
Реализуйте операции InitQueue, QueueEmpty, Enqueue и Dequeue для очереди целых чисел, представленной в виде 
кольцевого буфера. Начальный размер буфера – 4. В случае переполнения размер буфера должен увеличиваться в два раза.

Составьте программу circbuf.c, демонстрирующую работоспособность реализованных операций.

Формат входных данных. Первая строка, считываемая со стандартного потока ввода, содержит общее количество 
выполняемых операций n (0 < n <= 100 000). Каждая из следующих n строк содержит описание операции.

Операция либо имеет форму ENQ x (добавить число x в хвост очереди, -2 000 000 000 < x < 2 000 000 000), 
либо форму DEQ (удалить головной элемент из очереди), либо форму EMPTY (проверить пустоту очереди).

Можно считать, что последовательность операций составлена правильно, то есть перед каждой операцией DEQ очередь 
не пуста.

Формат результата работы программы. Для каждой операции DEQ вывести в стандартный поток вывода значение удаляемого 
головного элемента очереди. Для каждой операции EMPTY вывести в стандартный поток вывода «true» или «false» в 
зависимости от того, пуста очередь или нет.
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_OPERATIONS 3

typedef struct CircleBuffer {
    int *data;
    int cap;
    int count;
    int head;
    int tail;
} CircleBuffer;

void InitQueue(CircleBuffer *q, int n);

bool QueueEmpty(CircleBuffer q);

void Enqueue(CircleBuffer *q, int x);

int Dequeue(CircleBuffer *q);

int gettingOperationNumber(char *operation);

CircleBuffer operationRecognition(CircleBuffer *structCircleBuffer, char *operation, int *number);

void freeCircleBuffer(CircleBuffer *structCircleBuffer);

int main() {
    CircleBuffer structCircleBuffer;
    InitQueue(&structCircleBuffer, 4);
    char operation[6];
    int number;
    while (true) {
        scanf("%s", operation);
        if (0 == strcmp("END", operation)) {
            break;
        }
        structCircleBuffer = operationRecognition(&structCircleBuffer, operation, &number);
    }
    freeCircleBuffer(&structCircleBuffer);
    return 0;
}

void InitQueue(CircleBuffer *q, int n) {
    q->data = (int *) malloc(sizeof(int) * n);
    q->cap = n;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
}

bool QueueEmpty(CircleBuffer q) {
    return 0 == q.count;
}

void Enqueue(CircleBuffer *q, int x) {
    if (q->count == q->cap) {
        int i;
        q->data = realloc(q->data, 2 * q->cap * sizeof(int));
        for (i = 0; i < q->tail; ++i) {
            q->data[q->cap + i] = q->data[i];
        }
        q->tail = q->cap + i;
        q->cap *= 2;
    }
    q->data[q->tail] = x;
    q->tail = (q->tail + 1) % q->cap;
    ++q->count;
}

int Dequeue(CircleBuffer *q) {
    if (QueueEmpty(*q)) {
        printf("ERROR: devastation\n");
    }
    int x;
    x = q->data[q->head];
    q->head = (q->head + 1) % q->cap;
    --q->count;
    return x;
}

int gettingOperationNumber(char *operation) {
    const char *array_of_operation[] = {"ENQ", "DEQ", "EMPTY"};
    for (int i = 0; i < DEFAULT_OPERATIONS; ++i) {
        if (0 == strcmp(operation, array_of_operation[i])) {
            return i;
        }
    }
    return -1;
}

CircleBuffer operationRecognition(CircleBuffer *structCircleBuffer, char *operation, int *number) {
    switch (gettingOperationNumber(operation)) {
        case 0:
            scanf("%d", number);
            Enqueue(structCircleBuffer, *number);
            break;
        case 1:
            printf("%d\n", Dequeue(structCircleBuffer));
            break;
        case 2:
            printf("%s\n", (QueueEmpty((*structCircleBuffer)) ? "true" : "false"));
            break;
        case -1:
            printf("ERROR: wrong input operation\n");
            break;
    }
    return (*structCircleBuffer);
}

void freeCircleBuffer(CircleBuffer *structCircleBuffer) {
    free((*structCircleBuffer).data);
    (*structCircleBuffer).data = NULL;
}
