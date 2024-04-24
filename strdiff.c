/*//==============================================================================================================
Составьте функцию strdiff, выполняющую побитовое сравнение двух строк. Функция должна быть объявлена как

int strdiff(char *a, char *b)
{
        ...
}
Если строки равны, функция должна возвращать -1. В противном случае, она должна возвращать порядковый номер бита, 
до которого содержимое строк совпадает.
*///==============================================================================================================
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
