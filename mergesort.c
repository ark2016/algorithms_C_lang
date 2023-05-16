#include <stdio.h>

int abs(int a) {
    return a < 0 ? -a : a;
}

void insert_sort(int *arr, int start, int end) {
    for (int i = start + 1; i <= end; ++i) {
        int elem = arr[i];
        int loc = i - 1;
        while (loc >= start && abs(arr[loc]) > abs(elem)) {
            arr[loc + 1] = arr[loc];
            --loc;
        }
        arr[loc + 1] = elem;
    }
}

void merge(int *a, int k, int l, int m) {
    int auxiliary_subsequence[m - k + 1];
    int i, j, h;
    i = k;
    j = l + 1;
    h = 0;
    while (h < m - k + 1) {
        if (j <= m && (i == l + 1 || abs(a[j]) < abs(a[i]))) {
            auxiliary_subsequence[h] = a[j];
            ++j;
        } else {
            auxiliary_subsequence[h] = a[i];
            ++i;
        }
        ++h;
    }
    for (int i = h - 1; 0 <= i; --i) {
        a[i + k] = auxiliary_subsequence[i];
    }
}

void merge_sort_rec(int *arr, int low, int high) {
    if (high - low < 5) {
        insert_sort(arr, low, high);
    } else {
        int med = (low + high) / 2;
        merge_sort_rec(arr, low, med);
        merge_sort_rec(arr, med + 1, high);
        merge(arr, low, med, high);
    }
}


void mergesort(int *arr, int nel) {
    merge_sort_rec(arr, 0, nel - 1);
}

int main() {
    int number_of_number;
    scanf("%d", &number_of_number);
    int arr_of_int[number_of_number];
    for (int i = 0; i < number_of_number; ++i) {
        scanf("%d", &arr_of_int[i]);
    }
    mergesort(arr_of_int, number_of_number);
    for (int i = 0; i < number_of_number; ++i) {
        printf("%d ", arr_of_int[i]);
    }
    return 0;
}
