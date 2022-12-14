#include <stdio.h>

void bin_arr(unsigned long long x, int arr_64[]){
    for (int i = 0; i < 64; ++i){
        arr_64[i] =  x % 2 == 0 ? 0 : 1;
        x /= 2;
    }
}

int main(){
   unsigned long long a, b, m, result = 0;// c;
   int arr_b[64];
   scanf("%lld%lld%lld", &a, &b, &m);
   bin_arr(b,arr_b);
   for (int i = 0; i < 64; ++i){
//       c = result;
       result += a % m * arr_b[i] % m * (1 << i) % m;
//       if(result<c) printf("%d",i);
       result %= m;
   }
//   result %= m;
   printf("%llu", result);
//   for (int i = 0; i < 64; ++i) printf("%d",arr_b[64-i-1]);
   return 0;
}
