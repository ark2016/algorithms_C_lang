void bubblesort(unsigned long nel, int (*compare)(unsigned long i, unsigned long j),
                void (*swap)(unsigned long i, unsigned long j)) {
    if (1 < nel) {
        unsigned long int left, right;
        left = 0;
        right = nel - 1;
        while (left <= right) {
            for (int i = left; i < right; ++i) {
                if (1 == compare(i, i + 1)) {
                    swap(i, i + 1);
                }
            }
            --right;
            for (int i = right; i > left; --i) {
                if (-1 == compare(i, i - 1)) {
                    swap(i, i - 1);
                }
            }
            ++left;
        }
    }
}
