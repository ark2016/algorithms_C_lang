#include <stdio.h>

void swap(int *P, int j, int i);

int partition(int *P, int low, int high);

void SelectSort(int *P, int low, int high);

void QuickSort(int *P, int n, int m);

void QuickSortRec(int *P, int low, int high, int m);

int main() {
    int size_of_array, m;
    scanf("%d%d", &size_of_array, &m);
    int array[size_of_array];
    for (int i = 0; i < size_of_array; ++i) {
        scanf("%d", &array[i]);
    }
    QuickSort(array, size_of_array, m);
    for (int i = 0; i < size_of_array; ++i) {
        printf("%d\n", array[i]);
    }
    return 0;
}

void swap(int *P, int j, int i) {
    int tmp;
    tmp = P[i];
    P[i] = P[j];
    P[j] = tmp;
}

int partition(int *P, int low, int high) {
    int i;
    i = low;
    for (int j = low; j < high; ++j) {
        if (P[j] < P[high]) {
            swap(P, j, i);
            ++i;
        }
    }
    swap(P, high, i);
    return i;
}

void SelectSort(int *P, int low, int high) {
    int k;
    for (int j = high; j > low; --j) {
        k = j;
        for (int i = j - 1; i >= low; --i)
            if (P[i] > P[k]) {
                k = i;
            }
        swap(P, j, k);
    }
}

void QuickSort(int *P, int n, int m) {
    QuickSortRec(P, 0, n - 1, m);
}

void QuickSortRec(int *P, int low, int high, int m) {
    int q;
    if (high - low < m) {
        SelectSort(P, low, high);
    } else {
        if (low < high) {
            q = partition(P, low, high);
            QuickSortRec(P, low, q - 1, m);
            QuickSortRec(P, q + 1, high, m);
        }
    }
}
