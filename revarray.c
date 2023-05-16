#include <stdio.h>
#include <malloc.h>

void my_memcpy(void *destination, const void *source, size_t num) {
    unsigned char *destination_temp = (unsigned char *) destination;
    const unsigned char *source_temp = (const unsigned char *) source;
    if (num) {
        while (num) {
            *(destination_temp++) = *(source_temp++);
            --num;
        }
    }
}

void revarray(void *base, size_t nel, size_t width) {
    void *temp = malloc(width);
    for (size_t i = 0; i < nel / 2; ++i) {
        void *source = (void *) ((char *) base + i * width * sizeof(char));
        void *destination = (void *) ((char *) base + (nel - i - 1) * width * sizeof(char));
        my_memcpy(temp, destination, width);
        my_memcpy(destination, source, width);
        my_memcpy(source, temp, width);
    }
    free(temp);
}
