#include <stdio.h>
#include <malloc.h>

#define NUMBER_OF_ENG_LETTERS 26

void dsort(char *string) {
    int eng_alpha_count_arr[26] = {0};//нельзя 26 -> NUMBER_OF_ENG_LETTERS(
    size_t counter_of_alpha = 0;
    while (*(string + counter_of_alpha * sizeof(char))) {
        ++eng_alpha_count_arr[*(string + counter_of_alpha * sizeof(char)) - 'a'];
        ++counter_of_alpha;
    }
    size_t number_of_alpha = counter_of_alpha;
    counter_of_alpha = 0;
    for (size_t i = 0; i < NUMBER_OF_ENG_LETTERS; ++i) {
        while (eng_alpha_count_arr[i] && (counter_of_alpha <= number_of_alpha)) {
            string[(int) counter_of_alpha] = i + 'a';
            ++counter_of_alpha;
            --eng_alpha_count_arr[i];
        }
    }
}

int main() {
    char *string;
    string = (char *) malloc(1000001 * sizeof(char));
    scanf("%s", string);
    dsort(string);
    printf("%s\n", string);
    free(string);
    string = NULL;
    return 0;
}
