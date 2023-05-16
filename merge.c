#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>


struct PriorityQueueHeap {
    int k;
    int v;
};

struct PriorityQueue {
    struct PriorityQueueHeap *heap;
    int cap;
    int count;
};

bool QueueEmpty(struct PriorityQueue q) {
    return 0 == q.count;
}

void swapPriorityQueueHeap(struct PriorityQueueHeap *a, struct PriorityQueueHeap *b) {
    struct PriorityQueueHeap tmp = *a;
    *a = *b;
    *b = tmp;
}

int priorityQueueScreening(struct PriorityQueueHeap *arr, int n) {
    int capacity, i, left, right, j;
    capacity = 0;
    i = 0;
    while (i < n / 2) {
        left = i * 2 + 1;
        right = left + 1;
        j = left;
        if ((right < n) && (arr[right].v > arr[left].v)) {
            j = right;
        }
        if (arr[i].v >= arr[j].v) {
            return capacity;
        }
        swapPriorityQueueHeap(&arr[i], &arr[j]);
        i = j;
        capacity = i;
    }
    return capacity;
}

void InitPriorityQueue(struct PriorityQueue *q, int n) {
    q->cap = n;
    q->count = 0;
    q->heap = malloc(n * sizeof(struct PriorityQueueHeap));
}

struct PriorityQueueHeap dequeue(struct PriorityQueue *q) {
    if (QueueEmpty(*q)) {
        printf("%s\n", "ERROR: Queue is empty");
    }
    struct PriorityQueueHeap x;
    x = q->heap[0];
    q->heap[0].v = INT_MIN;
    q->count = priorityQueueScreening(q->heap, q->cap);
    return x;
}

void enqueue (struct PriorityQueue *q, struct PriorityQueueHeap ptr) {
    int i = q->count;
    if (i == q->cap) {
        printf("ERROR: overflow\n");
    }
    q->count = i + 1;
    q->heap[i] = ptr;
    while ((i > 0) && (q->heap[(i - 1) / 2].v < q->heap[i].v)) {
        swapPriorityQueueHeap(&q->heap[i], &q->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    int k;
    scanf("%d", &k);
    int n = 0;
    int n_i;
    for (int i = 0; i < k; ++i) {
        scanf("%d", &n_i);
        n += n_i;
    }
    struct PriorityQueue queue;
    InitPriorityQueue(&queue, n);
    for (int i = 0; i < n; ++i) {
        int input;
        scanf("%number", &input);
        struct PriorityQueueHeap number;
        number.k = input;
        number.v = -input;
        enqueue(&queue, number);
    }
    for (int i = 0; i < n; ++i)
        printf("%d ", dequeue(&queue).k);
    free(queue.heap);
    queue.heap = NULL;
    return 0;
}
