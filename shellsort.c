#include <stdio.h>
#include <malloc.h>

#define  MAX_INT_FIB_IDX 47

int *fibInt(int *intArr) {
    intArr = (int *) malloc(MAX_INT_FIB_IDX * sizeof (int));
    intArr[0] = 1;
    intArr[1] = 1;
    for (int i = 2; i < MAX_INT_FIB_IDX; ++i) {
        intArr[i] = intArr[i - 1] + intArr[i - 2];
    }
    return intArr;
}

int nearestFibonacci(int n, int *fibArr){
    int i;
    for(i = 0; i < MAX_INT_FIB_IDX && n < fibArr[i]; ++i);
    return fibArr[i];
}

void shellsort(unsigned long nel, int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j)) {
    int *fibIntArr = NULL;
    fibIntArr = fibInt(fibIntArr);
    for (int d = nearestFibonacci(nel, fibIntArr); d > 0; d = nearestFibonacci(d - 1, fibIntArr)) {
        for (int i = d; i < nel; ++i) {
            for (int j = i - d; (j >= 0) && (1 == compare(j, j + d)); j -= d) {
                swap(j, j + d);
            }
        }
    }
    free(fibIntArr);
    fibIntArr = NULL;
}
