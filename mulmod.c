#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
/*
unsigned long dif(const unsigned long x, const unsigned long y, const unsigned long m) {
    unsigned long ans = x - y;
    if (ans > x)
        ans += m;
    return ans;
}

bool check_ge_rounded_sqrt(const unsigned long m, const unsigned long r) {
    return ((r >= 1ull << 32) || r * (r + 1) >= m);
}

bool check_le_rounded_sqrt(const unsigned long m, const unsigned long r) {
    return (r == 0 || ((r <= 1ull << 32) && r * (r - 1) < m));
}

bool check_rounded_sqrt(const unsigned long m, const unsigned long r) {
    return check_ge_rounded_sqrt(m, r) && check_le_rounded_sqrt(m, r);
}

unsigned long rounded_sqrt(const unsigned long m) {
    unsigned long r = floor(.5 + sqrtl(m));
    if (!check_ge_rounded_sqrt(m, r)) {
        while (!check_ge_rounded_sqrt(m, ++r));
    } else if (!check_le_rounded_sqrt(m, r)) {
        while (!check_le_rounded_sqrt(m, --r));
    }
    return r;
}

unsigned long sum(const unsigned long x, const unsigned long y, const unsigned long m) {
    unsigned long ans = x + y;
    if (ans < x || ans >= m)
        ans -= m;
    return ans;
}

unsigned long prod_karatsuba_aux(const unsigned long x, const unsigned long N, const unsigned long m0, const unsigned long m) {
    unsigned long x1 = x / N;
    unsigned long x0N = (x - N * x1) * N;
    if (m0 >= 0)
        return dif(x0N, x1 * (unsigned long) m0, m);
    else
        return sum(x0N, x1 * (unsigned long) -m0, m);
}
/*
unsigned long prod_karatsuba(const unsigned long t) {
    unsigned long x = t.x, y = t.y, m = t.modulo;
    unsigned long N = rounded_sqrt(t.modulo);
    unsigned long m0 = m - N * N;
    unsigned long x1 = t.x / N;
    unsigned long x0 = t.x - N * x1;
    unsigned long y1 = t.y / N;
    unsigned long y0 = t.y - N * y1;
    unsigned long x0y0 = sum(x0 * y0, 0, m);
    unsigned long x0y1 = sum(x0 * y1, 0, m);
    unsigned long x1y0 = sum(x1 * y0, 0, m);
    unsigned long x1y1 = sum(x1 * y1, 0, m);
    return sum(prod_karatsuba_aux(sum(prod_karatsuba_aux(x1y1, N, m0, m), sum(x0y1, x1y0, m), m), N, m0, m), x0y0, m);
}
*/
bool is_overflow_plus(long *x, long *aa, int *more_plus, int *more_minus) {
    if ((*x >= 0) && (*aa > 0) && (*x + *aa < 0)) {
//        printf("|%ld %ld\n", *x, *aa);
        *more_plus += 1;
        *x -= LONG_MAX;
        return true;
    } else if ((*x < 0) && (*aa <= 0) && (*x + *aa > 0)) {
//        printf("|%ld %ld", *x, *aa);
        *more_minus -= 1;
        *x -= LONG_MIN;
        return true;
    }
    return false;
}

long mod_multiply(long aa, long bb, long m){
    long long result = 0;
    int more_plus = 0, more_minus = 0, difference = 0;
    aa %= m;
    bb %= m;
    for(long i = 0; i < bb; i++){
        is_overflow_plus(&aa,&bb,&more_plus,&more_minus);
        aa += bb;
        aa %= m;
    }
    difference = more_plus - more_minus;
    result = aa + difference + (more_plus - more_minus) * LONG_MAX;
    result %= m;
    printf("a %ld b %ld\nmore_plus %d more_minus %d\nanswer = %lld", aa,bb,more_plus,more_minus,result);
    /*
    while(b > 0){
        if (a + b < m) {
            a += b;
            b -= 1;
        }
        else{

        }
    */
}

int main(){
    long a, b, m, result;
    scanf("%ld%ld%ld", &a, &b, &m);
//    printf("%ld")
    mod_multiply(a,b,m);
} /*{
    unsigned long a, b, m, result = 0;
//    unsigned long long result = 0;
    scanf("%llu%llu%llu", &a, &b, &m);
    prod_karatsuba_aux(a,b,m,result);
    printf("%lu\n ", result);
    return 0;
}

/*
void bin(long n, char *b) {
    for (char i = 0; i < 64; i++) {
        b[63 - i] = n % 2;
        n /= 2;
    }
}

int main() {
    char bin_b[64];
    unsigned long a, b, m, result = 0;

    scanf("%ld%ld%ld", &a, &b, &m);
    bin(b, bin_b);
    for (short i = 0; i < 64; i++) {
        printf("%d %ld\n", bin_b[i], result);
//        result = ((result + (a * bin_b[i]) % m) * 2) % m;
        if (i < 63) result = ((result + (a * bin_b[i]) % m) * 2) % m;
        else result = (result + (a * bin_b[i]) % m)%m;
    }
    printf("\n  %ld", result);
    return 0;
}
*/
