/*//==============================================================================================================
Составьте функцию binsearch, выполняющую поиск заданного числа в последовательности чисел, отсортированной по 
возрастанию, методом деления пополам. Функция должна быть объявлена как

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
        ...
}
Здесь параметр nel задаёт количество элементов в последовательности, а параметр compare — указатель на функцию 
сравнения, которая принимает параметр i и и возвращает:

-1, если i-тое число в последовательности меньше искомого числа;
0, если они равны;
1, если i-тое число больше искомого числа.

Функция binsearch должна возвращать индекс найденного элемента или значение nel, если такого элемента не существует.
*///==============================================================================================================
unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) {
    unsigned long int middle = nel / 2, start = 0, finish = nel - 1;
    while (start <= finish) {
        int comparison_result = compare(middle);
        if (1 == comparison_result) finish = middle - 1;
        else if (-1 == comparison_result) start = middle + 1;
        else return middle;
        middle = (start + finish) / 2;
    }
    return nel;
}
