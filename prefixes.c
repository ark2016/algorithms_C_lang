#include <stdio.h>
#include <string.h>

void print_prefixes(char *string, size_t string_len){
    int p[string_len];
    p[0] = 0;
    for (size_t i = 1; i < string_len; ++i){
        int j = p [i - 1];
        while ((j > 0) && (string[i] != string[j])){
            j = p[j - 1];
        }
        if (string[i] == string[j]){
            ++j;
        }
        p[i] = j;
        int k = i + 1;
        if((p[i] > 0) && (0 == k % (k - p[i]))){
            printf("%d %d\n", k, k / (k-p[i]));
        }
    }
}

int main(int argc, char **argv) {
    char *string = argv[1];
    size_t string_len = strlen(string);
    print_prefixes(string, string_len);
    return 0;
}
