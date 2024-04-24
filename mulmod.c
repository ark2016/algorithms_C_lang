/*//==============================================================================================================
Составьте программу mulmod.c, вычисляющую выражение (a*b)mod(c), то есть остаток от деления произведения чисел 
a и b на c. Известно, что a, b и c  — натуральные числа, меньшие, чем 2^63, причем m != 0.

Программа должна считывать из стандартного потока ввода числа  a, b и c и выводить результат в стандартный поток 
вывода.

Основная сложность этой задачи заключается в том, что произведение a на b может превышать 2^64 и, тем самым, не 
помещаться ни в один из целочисленных типов данных языка C. При этом представление формулы в виде 
((a mod(c)) (b mod(c))) mod(c) тоже не решает проблемы, так как при больших значениях произведение 
(a mod(c)) (b mod(c)) тоже может превышать 2^64
*///==============================================================================================================
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
