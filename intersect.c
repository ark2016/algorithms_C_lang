/*//==============================================================================================================
Пусть N_32 — множество натуральных чисел от 0 до 31. Даны два множества A <= N_32 и B <= N_32. Составьте программу 
intersect.c, вычисляющую пересечение множеств A и B.

Программа должна считывать из стандартного потока ввода размер множества A и элементы множества A, а затем — размер
множества B и элементы множества B. Программа должна выводить в стандартный поток вывода элементы множества A & B, 
отсортированные в порядке возрастания.

Использовать массивы для хранения множеств запрещается: каждое множество должно быть представлено 32-разрядным 
целым числом таким, что если его i-й бит равен 1, то число i принадлежит множеству.
*///==============================================================================================================
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
