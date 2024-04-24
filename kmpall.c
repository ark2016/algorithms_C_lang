/*//==============================================================================================================
Составьте программу kmpall.c, осуществляющую поиск всех вхождений подстроки S в строку T. В программе должен быть 
реализован алгоритм Кнута–Морриса–Пратта, изменённый таким образом, чтобы при нахождении очередного вхождения S в 
T алгоритм не завершался, а продолжал сканировать строку T.

Строки S и T должны передаваться в программу через аргументы командной строки. Программа должна выводить в 
стандартный поток вывода индексы первых символов всех вхождений S в T.
*///==============================================================================================================
#include <stdio.h>
#include <string.h>
#include <malloc.h>

void prefix_function(char *s, int *pi, size_t n) {
    pi[0] = 0;
    for (size_t i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while ((j > 0) && (s[i] != s[j]))
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
}

int kmpall(char *string, char *substring, int *indices[]) {
    int string_len, substring_len;
    substring_len = strlen(substring);
    string_len = strlen(string);
    int pi[substring_len];
    prefix_function(substring, pi, substring_len);
    int *auxiliary_array = NULL;
    int counter, q;
    counter = 0;
    q = 0;
    for (int k = 0; k < string_len; ++k) {
        while (q > 0 && substring[q] != string[k])
            q = pi[q - 1];
        if (substring[q] == string[k])
            ++q;
        if (q == substring_len) {
            auxiliary_array = (int *) realloc(auxiliary_array, sizeof(int) * ++counter);
            auxiliary_array[counter - 1] = k - q + 1;
        }
    }
    *indices = auxiliary_array;
    return counter;
}

int main(int argc, char **argv) {
    char *substring = argv[1];
    char *string = argv[2];
    int *indices;
    int number_of_occurrences;
    number_of_occurrences = kmpall(string, substring, &indices);
    for (int i = 0; i < number_of_occurrences; ++i) {
        printf("%d\n", indices[i]);
    }
    free(indices);
    indices = NULL;
    return 0;
}
