#include <stdio.h>
#include <stdbool.h>

void scan_long_long_arr_top_8(long long arr[]){
    long long input;
    for (int i = 0; i < 8; ++i){
        scanf("%lld",&input);
        arr[i] = input;
    }
}

bool find_element_in_array_top_8(long long arr[], long long elem){
    for(int i = 0; i < 8; ++i)
        if (arr[i] == elem) return true;
    return false;
}
bool permut_top_8(long long arr1[], long long arr2[]){
    bool fl = true;
    for (int i = 1; i < 8; ++i)
        fl = fl && find_element_in_array_top_8(arr1, arr2[i]);
    return fl;
}

int main() {
    long long A[8], B[8], input;
    scan_long_long_arr_top_8(A);
    scan_long_long_arr_top_8(B);

    if (permut_top_8(A,B))
        printf("yes");
    else
        printf("no");
    return 0;
}
