#include <stdio.h>

int wcount(char *s) {
    size_t counter_of_alpha = 0;
    int counter_of_words = 0, is_last_alpha = 0;
    while ('\0' != *(s + counter_of_alpha * sizeof(char))) {
        if (' ' == *(s + counter_of_alpha * sizeof(char))) {
            if (0 != is_last_alpha) {
                ++counter_of_words;
            }
            is_last_alpha = 0;
        } else {
            is_last_alpha = 1;
        }
        ++counter_of_alpha;
        if (('\0' == *(s + counter_of_alpha * sizeof(char))) && (0 != is_last_alpha)) {
            ++counter_of_words;
        }
    }
    return counter_of_words;
}

int main() {
//    char arr[10] = {'a', 'b',' ',' ',' ', 'a', 'b', '1', '\0'};
    char masstr[1024];
    char *rstr;
    rstr = gets(masstr);
//    printf ("Считана строка:\n%s\n",masstr);
    printf("%d\n", wcount(masstr));
    return 0;
}
