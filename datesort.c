/*//==============================================================================================================
Составьте программу datesort.c, осуществляющую сортировку последовательности дат по возрастанию. В программе 
должен быть реализован алгоритм поразрядной сортировки, адаптированный для случая, когда ключи представляются в 
системе счисления с основаниями, зависящими от разряда.

В программе сортируемая последовательность должна быть представлена в виде массива структур Date:

struct Date {
    int Day, Month, Year;
};
Поле Day может принимать значения от 1 до 31, поле Month — от 1 до 12, а поле Year — от 1970 до 2030.

Последовательность дат считывается из стандартного потока ввода. При этом в самом начале считывается общее количество 
дат, а каждая дата представляется тройкой чисел «yyyy mm dd».

Например, если введена последовательность

5
2005 01 12
1977 02 01
1994 03 01
2004 02 29
1977 08 01
то программа должна выводить в стандартный поток вывода

1977 02 01
1977 08 01
1994 03 01
2004 02 29
2005 01 12
Указание. Формат вывода для printf(): "%04d %02d %02d".
*///==============================================================================================================
#include <stdio.h>
#include <malloc.h>

struct Date {
    int Day, Month, Year;
};

int get_value(struct Date date, int key) {
    if (key == 0) return date.Day;
    if (key == 1) return date.Month;
    if (key == 2) return date.Year;
}

int get_size_of_count_date(int key) {
    if (key == 0) return 32;
    if (key == 1) return 13;
    if (key == 2) return 2031;
}

void distribution_sort(int key, struct Date arr_of_date[], int number_of_dates) {
    int size_of_count_date = (get_size_of_count_date(key));
    int count[size_of_count_date];
    for (int i = 0; i < size_of_count_date; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < number_of_dates; ++i) {
        int k = get_value(arr_of_date[i], key);
        ++count[k];
    }
    for (int i = 1; i < size_of_count_date; ++i) {
        count[i] += count[i - 1];
    }
    struct Date auxiliary_array[number_of_dates];
    for (int j = number_of_dates - 1; 0 <= j; --j) {
        int k = get_value(arr_of_date[j], key);
        int i = count[k] - 1;
        count[k] = i;
        auxiliary_array[i] = arr_of_date[j];
    }
    for (int i = 0; i < number_of_dates; ++i) {
        arr_of_date[i] = auxiliary_array[i];
    }
}


void radix_sort(struct Date arr_of_date[], int number_of_date) {
    for (int key = 0; key < 3; ++key) {
        distribution_sort(key, arr_of_date, number_of_date);
    }
}


int main() {
    int number_of_date;
    scanf("%d", &number_of_date);
    struct Date *arr_of_dates = (struct Date*)malloc((size_t) number_of_date * sizeof(struct Date));
    for (int i = 0; i < number_of_date; ++i) {
        scanf("%d%d%d", &arr_of_dates[i].Year, &arr_of_dates[i].Month, &arr_of_dates[i].Day);
    }
    radix_sort(arr_of_dates, number_of_date);
    for (int i = 0; i < number_of_date; ++i) {
        printf("%04d %02d %02d\n", arr_of_dates[i].Year, arr_of_dates[i].Month, arr_of_dates[i].Day);
    }
    free(arr_of_dates);
    arr_of_dates = NULL;
    return 0;
}
