#include <stdio.h>

int main() {
    int n, k;
    long long result = 0, intermediate_result = 0;
    scanf("%d", &n);
//    scanf("%d", &k);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
        intermediate_result += arr[i];
    }
    result = intermediate_result;
    if (k != n) {
        for (int i = k; i < n; ++i) {
            intermediate_result += arr[i] - arr[i - k];
            if (intermediate_result > result) result = intermediate_result;
        }
    }
    printf("%lld\n", result);
    return 0;
}
