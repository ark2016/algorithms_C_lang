#include <stdio.h>

void fib(long long num) {
    int m = 92;
    long long A[m + 1];
    int answer[93] ={0};
    A[0] = 1;
    A[1] = 1;
    for (int i = 2; i < m; ++i) {
        A[i] = A[i - 1] + A[i - 2];
    }
    for (int i = 2; i <= m; ++i) {
        if (A[m - i + 1] <= num) {
            num -= A[m - i + 1];
            answer[i] = 1;
        }
    }
    int fl = 0;
    for (int  i = 0; i < m + 1; ++i){
        fl += answer[i];
        if (fl > 0){
            printf("%d",answer[i]);
        }
    }
    if (0 == fl) printf("0");
}

int main() {
    long long x;
    scanf("%lld", &x);
    fib(x);
    return 0;
}
