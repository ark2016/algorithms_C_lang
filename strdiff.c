#include <stdio.h>

int bit_chek_char_diff(char *a, char *b) {
    for (int i = 0; i < 8; ++i) {
        if (((*a >> i) & 1) != (((*b >> i) & 1))) {
            return i;
        }
    }
}

int strdiff(char *a, char *b) {
    size_t counter = 0;
    while (('\0' != *(a + counter * sizeof(char))) || ('\0' != *(b + counter * sizeof(char)))) {
        if (*(a + counter * sizeof(char)) != *(b + counter * sizeof(char)))
            return counter * 8 + bit_chek_char_diff((a + counter * sizeof(char)), (b + counter * sizeof(char)));
        ++counter;
    }
    return -1;
}
