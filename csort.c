/*//==============================================================================================================
Составьте функцию сsort, выполняющую сортировку слов в предложении методом подсчёта сравнений. Слова в предложении 
разделяются произвольным количеством пробелов. Функция csort должна быть объявлена следующим образом:

void csort(char *src, char *dest)
{
        ...
}
В качестве параметров функция csort принимает указатель на исходное предложение src и указатель на пустой буфер dest
подходящего размера. В результате работы функции в буфер dest записывается новое предложение, состоящее из слов, 
взятых из исходного предложения и отсортированных в порядке возрастания их длин. При этом слова в новом предложении 
разделяются одним пробелом.

Рассмотрим пример работы функции csort. Пусть исходное предложение выглядит как

qqq  www  t  aa rrr  bb  x y zz
Тогда в выходной буфер должно быть записано предложение

t x y aa bb zz qqq www rrr
Итоговую программу, содержащую как функцию csort, так и функцию main, демонстрирующую работоспособность функции 
csort, нужно назвать csort.c. Программа должна считывать исходное предложение со стандартного потока ввода.

Минимальный размер буфера для ввода с консоли должен быть равен 1000 символов включая \0 в конце строки.
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define BUFFER 1024

size_t my_strlcat(char *destionation, const char *source, size_t size) {
    size_t count;
    count = 0;
    while (destionation[count] && count < size)
        count++;
    size -= count;
    if (size) {
        if ('\0' != destionation[0] && (0 < strlen(source))) {
            destionation[count] = ' ';
            ++count;
            ++size;
        }
        while (*source != '\0' && 0 < size) {
            destionation[count] = *source;
            count++;
            source++;
            size--;
        }
        destionation[count] = '\0';
    }
    return (count);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int wcount(char *s, int *maxlen) {
    size_t counter_of_alpha = 0;
    int counter_of_words = 0, is_last_alpha = 0, len = 0;
    while ('\0' != *(s + counter_of_alpha * sizeof(char))) {
        if (' ' == *(s + counter_of_alpha * sizeof(char))) {
            if (0 != is_last_alpha) {
                ++counter_of_words;
                *maxlen = max(*maxlen, len);
            }
            is_last_alpha = 0;
            len = 0;
        } else {
            is_last_alpha = 1;
            ++len;
        }
        ++counter_of_alpha;
        if (('\0' == *(s + counter_of_alpha * sizeof(char))) && (0 != is_last_alpha)) {
            ++counter_of_words;
            *maxlen = max(*maxlen, len);
        }
    }
    return counter_of_words;
}

void my_cont(char **c_matrix, char *src) {
    size_t counter_of_alpha = 0;
    while ('\0' != *(src + counter_of_alpha * sizeof(char))) {
        size_t i = counter_of_alpha;

        int len = 0;
        while ('\0' != *(src + i * sizeof(char)) && (' ' != *(src + i * sizeof(char)))) {
            ++i;
            ++len;
        }
        if ('\0' == *(src + i * sizeof(char))) {
            my_strlcat(c_matrix[len - 1], &src[counter_of_alpha], BUFFER);
            return;
        } else {
            src[i] = '\0';
            my_strlcat(c_matrix[len - 1], &src[counter_of_alpha], BUFFER);
        }
        do ++i;
        while (' ' == *(src + i * sizeof(char)));
        counter_of_alpha = i;
    }
}

void csort(char *src, char *dest) {
    int maxlen = 0;
    wcount(src, &maxlen);
    char **c_matrix = malloc(maxlen * sizeof(char *));
    for (int i = 0; i < maxlen; i++) {
        c_matrix[i] = malloc(BUFFER * sizeof(char));
    }
    dest[0] = '\0';
//    char **c_matrix = (char **) malloc(number_of_words * sizeof(char *) + number_of_words * BUFFER * sizeof(char));
    for (int i = 0; i < maxlen; ++i) {
        c_matrix[i][0] = '\0';
    }
    my_cont(c_matrix, src);
    my_strlcat(dest, c_matrix[0], BUFFER);
    for (int i = 1; i < maxlen; ++i) {
        my_strlcat(dest, c_matrix[i], BUFFER);
    }
    for (int i = 0; i < maxlen; i++) {
        free(c_matrix[i]);
        c_matrix[i] = NULL;
    }
    free(c_matrix);
}

int main() {
    char destination[BUFFER];
    char source[BUFFER];
    char *rstr;
    rstr = gets(source);
    csort(source, destination);
    printf("%s", destination);
    return 0;
}
