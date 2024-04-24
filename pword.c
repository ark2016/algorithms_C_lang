/*//==============================================================================================================
Составьте программу pword.c, определяющую, составлена ли строка T исключительно из префиксов строки S.

Программа получает строки S и T через аргументы командной строки и выводит «yes», если T составлена из префиксов S,
и «no» — в противном случае.

Например, пусть программа вызвана как

./pword abracadabra abrabracada
Тогда программа должна выводить в стандартный поток вывода «yes».
*///==============================================================================================================
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void prefix_function(const char *s, int *pi, size_t n) {
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

bool is_made_of_prefixes(char *string, char *t_string) {
    int string_len, t_string_len;
    string_len = strlen(string);
    t_string_len = strlen(t_string);
    int pi[string_len];
    prefix_function(string, pi, string_len);
    int q = 0;
    for (size_t k = 0; k < t_string_len; ++k) {
        while ((q > 0) && (string[q] != t_string[k])) {
            q = pi[q - 1];
        }
        if (string[q] == t_string[k]) {
            ++q;
        }
        if (q == 0) {
            return false;
        }
        if (q == strlen(string)) {
            q = pi[q - 1];
        }
    }
    return true;
}

int main(int argc, char **argv) {
    char *string = argv[1];
    char *t_string = argv[2];
    if (is_made_of_prefixes(string, t_string)) {
        printf("yes");
    } else {
        printf("no");
    }
    return 0;
}
