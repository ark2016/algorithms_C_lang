#include <stdio.h>

#define RADIX 4
#define BASE 256

union Int32 {
    int x;
    unsigned char bytes[4];
};

int key(union Int32 int_32, int radix) {
    return int_32.bytes[radix];
}

void distribution_sort(int base, int radix, union Int32 arr_of_numbers[], int number_of_numbers) {
    int count[base];
    for (int i = 0; i < base; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < number_of_numbers; ++i) {
        int k = key(arr_of_numbers[i], radix);
        if (radix == 3) k ^= 128;
        ++count[k];
    }
    for (int i = 1; i < base; ++i) {
        count[i] += count[i - 1];
    }
    union Int32 auxiliary_array[number_of_numbers];
    for (int j = number_of_numbers - 1; 0 <= j; --j) {
        int k = key(arr_of_numbers[j], radix);
        if (radix == 3) k ^= 128;
        int i = count[k] - 1;
        count[k] = i;
        auxiliary_array[i] = arr_of_numbers[j];
    }
    for (int i = 0; i < number_of_numbers; ++i) {
        arr_of_numbers[i] = auxiliary_array[i];
    }
}

void radix_sort(int base, int radix, union Int32 arr_of_numbers[], int n) {
    for (int i = 0; i < radix; ++i) {
        distribution_sort(base, i, arr_of_numbers, n);
    }
}

int main() {
    int number_of_numbers;
    scanf("%d", &number_of_numbers);
    union Int32 arr_of_numbers[number_of_numbers];
    for (int i = 0; i < number_of_numbers; ++i) {
        scanf("%d", &arr_of_numbers[i].x);
    }
    radix_sort(BASE, RADIX, arr_of_numbers, number_of_numbers);
    for (int i = 0; i < number_of_numbers; ++i) {
        printf("%d ", arr_of_numbers[i].x);
    }
    return 0;
}
