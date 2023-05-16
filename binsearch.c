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
