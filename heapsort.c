/*//==============================================================================================================
Составьте функцию hsort, выполняющую пирамидальную сортировку произвольного массива. Объявление функции hsort 
должно быть выполнено по аналогии с функцией qsort:

void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b))
{
        ...
}
В качестве параметров функция hsort принимает указатель на начало массива base, количество элементов массива 
nel, размер одного элемента width и указатель на функцию сравнения compare.

Замечание. Функция hsort должна иметь тот же интерфейс, что и функция qsort. А функция qsort предполагает, 
что функция compare возвращает отрицательное значение, когда a < b, ноль, когда a == b, и положительное значение, 
когда a > b. Т.е. функция compare не обязательно возвращает только -1, 0 или +1. См., например, здесь:

https://en.cppreference.com/w/c/algorithm/qsort
http://cplusplus.com/reference/cstdlib/qsort/ (внимание на пример!)
Итоговая программа heapsort.c должна сортировать массив строк в порядке возрастания количества букв a в строке. 
Программа должна считывать из стандартного потока ввода размер и элементы массива, и выводить в стандартный поток 
вывода результат сортировки.

Минимальный размер буфера для ввода с консоли должен быть равен 1000 символов включая \0 в конце строки.
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>

#define BUFFER 1024

int count_of_a_in_str(const char *s) {
    size_t counter = 0;
    int counter_of_a = 0;
    while ('\0' != *(s + counter * sizeof(char))) {
        if ('a' == *(s + counter * sizeof(char))) {
            ++counter_of_a;
        }
        ++counter;
    }
    return counter_of_a;
}

int compare(const void *a, const void *b) {
    int a_in_a, a_in_b;
    a_in_a = count_of_a_in_str(a);
    a_in_b = count_of_a_in_str(b);
    return a_in_a - a_in_b;
}

void my_memcpy(void *destination, const void *source, size_t num) {
    unsigned char *destination_temp = (unsigned char *) destination;
    const unsigned char *source_temp = (const unsigned char *) source;
    if (num) {
        while (num) {
            *(destination_temp++) = *(source_temp++);
            --num;
        }
    }
}

void swap(void *a, void *b, size_t width) {
    void *temp = malloc(width);
    my_memcpy(temp, a, width);
    my_memcpy(a, b, width);
    my_memcpy(b, temp, width);
    free(temp);
}

void heapify(void *base, int i, size_t n, size_t width, int (*compare)(const void *a, const void *b)) {
    for (;;) {
        int l, r, j;
        l = 2 * i + 1;
        r = l + 1;
        j = i;
        if ((l < (int) n) &&
            (0 > compare((void *) ((char *) base + i * width), (void *) ((char *) base + l * width)))) {
            i = l;
        }
        if ((r < (int) n) &&
            (0 > compare((void *) ((char *) base + i * width), (void *) ((char *) base + r * width)))) {
            i = r;
        }
        if (i == j) {
            break;
        }
        swap((char *) base + i * width, (char *) base + j * width, width);
    }
}

void build_heap(void *base, size_t nel, size_t width, int (*compare)(const void *a, const void *b)) {
    int i = nel / 2 - 1;
    while (0 <= i) {
        heapify(base, i, nel, width, compare);
        --i;
    }
}

void hsort(void *base, size_t nel, size_t width, int (*compare)(const void *a, const void *b)) {
    build_heap(base, nel, width, compare);
    size_t i = nel - 1;

    while (0 < i) {
        swap(base, (void *) ((char *) base + i * width), width);
        heapify(base, 0, (int) i, width, compare);
        --i;
    }
}

int main() {
    int number_of_strings;
    scanf("%d ", &number_of_strings);
    char arr_of_strings[number_of_strings][BUFFER];
    for (int i = 0; i < number_of_strings; ++i) {
        scanf("%s", arr_of_strings[i]);
    }
    hsort(arr_of_strings, number_of_strings, BUFFER, compare);
    for (int i = 0; i < number_of_strings; ++i) {
        printf("%s\n", arr_of_strings[i]);
    }
    return 0;
}
