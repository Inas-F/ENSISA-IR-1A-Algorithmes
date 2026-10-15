#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Naive Fibonacci

long long fibonacci(int n) { // Calcule le n-ième élément de la suite de Fibonacci
    if (n==0 || n==1) {
        return n;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

// Dynamic Programming Fibonacci

long long dp_fibonacci(int n, long long DPFib[]) {
    if (n<=1){
        return n;
    }
    if (DPFib[n] != -1){
        return DPFib[n];
    }
    DPFib[n] = dp_fibonacci(n-1, DPFib) + dp_fibonacci(n-2, DPFib);
    return DPFib[n];
}

int main() {
    const int n = 40;
    long long DPFib[n + 1];

    for (int i = 0; i < n + 1; i++) {
        DPFib[i] = -1;
    }

    //  Time naive Fibonacci
    clock_t start_naive = clock();
    long long res_naive = fibonacci(n);
    clock_t end_naive = clock();
    double time_naive = (double)(end_naive - start_naive) / CLOCKS_PER_SEC;

    // Time db Fibonacci
    clock_t start_dp = clock();
    long long res_dp = dp_fibonacci(n, DPFib);
    clock_t end_dp = clock();
    double time_dp = (double)(end_dp - start_dp) / CLOCKS_PER_SEC;

    printf("Temps Naif      : %f secondes \n", time_naive);
    printf("Temps Dynamique : %f secondes \n", time_dp);
    return 0;
}