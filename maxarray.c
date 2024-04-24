/*//==============================================================================================================
Составьте функцию maxarray, возвращающую индекс максимального элемента произвольного массива. Функция должна быть 
объявлена как

int maxarray(void *base, size_t nel, size_t width,
        int (*compare)(void *a, void *b))
{
        ...
}
Здесь параметр base означает указатель на начало массива, nel — количество элементов в массиве, width — размер 
каждого элемента массива в байтах, а compare — указатель на функцию сравнения двух элементов, работающую аналогично 
функции сравнения для библиотечной функции qsort.

Примечание. Тип size_t определён в заголовочных файлах <stddef.h>, <stdio.h>, <stdlib.h>, <string.h>, <time.h> и 
<wchar.h>.
*///==============================================================================================================
#include <stdio.h>

int maxarray(void *base, size_t nel, size_t width, int (*compare)(void *a, void *b)) {
    size_t max_id = 0;
    void *res = base;
    for (size_t i = 1; i < nel; ++i) {
        void *now = (void *) ((char *) base + i * width * sizeof(char));
        if ((compare(res, now)) < 0) {
            res = now;
            max_id = i;
        }
    }
    return (int) max_id;
}


static const int input_int[] = {3, 8, 6, 7, 1, 2, 5, 9, 4};

static int cmp_int(void *va, void *vb) {
    int a = *(int *) va;
    int b = *(int *) vb;
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}


int main() {
    printf("main %u\n", sizeof(int));
    printf("%d", maxarray((void *) input_int, (size_t) 9, sizeof(int), cmp_int));
    return 0;
}
