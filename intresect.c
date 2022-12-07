#include <stdio.h>
#include <stdbool.h>

bool check_bit(int a, int b) {
    return (a | (2 << b)) == a;
}

int set_bit(int a, int b) {
    return a | (2 << b);
}

int set_wrtite(int size) {
    int input;
    long set = 0;
    for (int i = 0; i < size; ++i) {
        scanf("%d", &input);
        if (!check_bit(set, input))
            set = set_bit(set, input);
//        printf("|%ld i = %d|",set,i);
    }
    return set;
}

void intresect_int(int set1, int set2){
    int answer = 0;
    answer = set1 & set2;
//    printf("set1 %d set2 %d answer %d\n",set1,set2,answer);
    for (int i = 0; i < 31; ++i){
        if (check_bit(answer, i))
            printf("%d ",i);
    }
}

int main() {
    int a_size, b_size, input;
    long A, B;
    scanf("%d", &a_size);
    A = set_wrtite(a_size);
    scanf("%d", &b_size);
    B = set_wrtite(b_size);
    intresect_int(A,B);
    return 0;
}
