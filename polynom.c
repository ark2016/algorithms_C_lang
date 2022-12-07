#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

bool is_overflow_plus(long long *x, long *a, int *more_plus, int *more_minus) {
    if ((*x >= 0) && (*a > 0) && (*x + *a < 0)) {
        printf("|%lld %ld\n", *x, *a);
        *more_plus += 1;
        *x -= LLONG_MAX;
        return true;
    } else if ((*x < 0) && (*a <= 0) && (*x + *a > 0)) {
        printf("|%lld %ld", *x, *a);
        *more_minus -= 1;
        *x -= LLONG_MIN;
        return true;
    }
    return false;
}

bool is_overflow_multiply(long long *x, long *x0, int *more_plus, int *more_minus) {
    if ((*x > *x0) ? LLONG_MAX / *x0 > *x : LLONG_MAX / *x > *x0) return false;
    long i = 1;
    long long result = *x;
    while (i < *x0) {
        ++i;
        is_overflow_plus(&result, x, more_plus, more_minus);
        result += *x;
    }
    *x = result;
    return true;
}

int main() {
    int n;
    int more_res_minus = 0, more_res_plus = 0, more_deriv_res_minus = 0, more_deriv_res_plus = 0;
    long x0, now;//, result = 0, derivate_result = 0;
    long long result = 0, derivate_result = 0;
//    long double result = 0, derivate_result = 0;
    scanf("%d %ld", &n, &x0);
    for (int i = 0; i <= n; i++) {
        scanf("%ld", &now);
        is_overflow_plus(&result, &now, &more_res_plus, &more_res_minus);
        if (i < n) {
//            result = result + now) * x0;
            result += now;
            is_overflow_multiply(&result,&x0,&more_res_plus, &more_res_minus);
        } else {
            result = result + now;
        }

        if (i < n - 1) {
            is_overflow_plus(&derivate_result, &now, &more_deriv_res_plus, &more_deriv_res_minus);
            derivate_result = (derivate_result + now * (n - i)) * x0;
//            printf(" derivate_result = %ld now = %ld n = %d\n", derivate_result, now, n - i);
        } else if (i == n - 1) {
            derivate_result = derivate_result + now;
        }
    }
    printf("%lld + %ld %ld\n%lld + %ld %ld\n", result, more_res_plus, more_res_minus, derivate_result,
           more_deriv_res_minus, more_deriv_res_plus);
//    printf("%lld\n%lld\n",  result, derivate_result);
    return 0;
}
