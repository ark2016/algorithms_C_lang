/*//==============================================================================================================
Имеется вычислительный кластер, состоящий из N однопроцессорных узлов. На кластере нужно выполнить M задач. Каждая 
задача описывается парой (t1, t2), где t1 — время в микросекундах от включения кластера, начиная с которого задачу 
можно посылать на выполнение (до этого времени входные данные для задачи неготовы); t2 — прогнозируемое время 
выполнения задачи в микросекундах.

Для выполнения каждой задачи задействуется один узел кластера, то есть задачи невозможно распараллеливать. 
Кроме того, нельзя менять порядок выполнения задач: если данные для задачи A оказываются подготовлены раньше, чем 
данные для задачи B, то задача A не может быть запущена позже задачи B.

Необходимо составить программу cluster.c, вычисляющую минимальное время в микросекундах от начала работы кластера, 
когда все задачи будут выполнены. В программе нужно использовать очередь с приоритетами для хранения времен 
окончания задач, запущенных на кластере.

Формат входных данных программы должен быть такой: первая строка, считываемая со стандартного потока ввода, 
содержит количество N узлов кластера, вторая строка содержит число M задач, каждая из следующих M строк содержит 
пару целых чисел (t1, t2), описывающих задачу. Пары чисел отсортированы в порядке возрастания t1, и, более того,
в каждой паре t1 уникально.

Программа должна вывести в стандартный поток вывода целое число, выражающее время в микросекундах, прошедшее от 
включения кластера до момента, когда все задачи будут выполнены.
*///==============================================================================================================
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <limits.h>

struct TaskTime {
    int start;
    int duration;
};

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
    q->heap = (struct PriorityQueueHeap *) malloc(sizeof(struct PriorityQueueHeap) * n);
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

void enqueue(struct PriorityQueue *q, struct PriorityQueueHeap ptr) {
    int i = q->count;
    if (i == q->cap) {
        printf("ERROR: overflow\n");
    }
    q->count++;
    q->heap[i] = ptr;
    while (i > 0 && q->heap[i].v > q->heap[(i - 1) / 2].v) {
        swapPriorityQueueHeap(&q->heap[i], &q->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int cluster(int number_of_tasks, const struct TaskTime *tasks, struct PriorityQueue *queue) {
    int total_time = 0;
    for (int i = 0; i < number_of_tasks; ++i) {
        struct TaskTime task = tasks[i];
        int time = dequeue(queue).k;
        if (task.start > time) {
            time = task.start;
        }
        time += task.duration;
        if (total_time < time) {
            total_time = time;
        }
        struct PriorityQueueHeap priorityQueueHeap;
        priorityQueueHeap.k = time;
        priorityQueueHeap.v = -time;
        enqueue(queue, priorityQueueHeap);
    }
    return total_time;
}


int main() {
    int number_of_cluster_nodes;
    struct PriorityQueue queue;
    struct PriorityQueueHeap structPriorityQueueHeap;
    scanf("%d", &number_of_cluster_nodes);
    InitPriorityQueue(&queue, number_of_cluster_nodes);
    structPriorityQueueHeap.k = 0;
    structPriorityQueueHeap.v = 0;
    for (int i = 0; i < number_of_cluster_nodes; ++i)
        enqueue(&queue, structPriorityQueueHeap);
    int number_of_tasks;
    scanf("%d", &number_of_tasks);
    struct TaskTime tasks[number_of_tasks];
    for (int i = 0; i < number_of_tasks; ++i) {
        int start, duration;
        scanf("%d %d", &start, &duration);
        tasks[i].start = start;
        tasks[i].duration = duration;
    }
    int total_time;
    total_time = cluster(number_of_tasks, tasks, &queue);
    printf("%d\n", total_time);
    free(queue.heap);
    queue.heap = NULL;
    return 0;
}
