#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int is_sorted_increasing(int A[], int n) {
    if (n <= 1) return 1;
    int old = A[0];
    for (int i = 1; i<n; i++) {
        int new = A[i];
        if (new <= old) {
            return 0;
        }
        old = new;
    }
    return 1;
}

int linear_search(int A[], int n, int x) {
    for (int i = 0; i<n; i++) {
        if (A[i] == x) {
            return i; // the target x is found in A
        }
    }
    return -1; // the target x is not found in A
}
//Worst case time complexity is if x is at the end of A, O(n)

int jump_search(int A[], int n, int x) {
    if (!is_sorted_increasing(A, n)) return -1; // error Array not strictly increasing
    int jump = (int)sqrt(n); // calculating the optimal jump
    int m = jump;
    int prev = 0;

    while (A[((m < n) ? m : n) - 1 ]< x){
        prev = m;
        m += jump;
        if (prev >=n) return -1;
    }
    for (int i = prev; i < ((m < n) ? m : n); i++) {
        if (A[i] == x) {    // the target x is found in A
            return i;   
        }
    }
    return -1; // the target x is not found in A
}
//Worst case time complexity is if x is at the end of A, but thanks to the jump being sqrt(n) the complexity is O(sqrt(n))

int binary_search(int A[], int n, int x){
    if (!is_sorted_increasing(A, n)) return -1; // error Array not strictly increasing
    int low = 0;
    int high = n-1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (A[mid] == x) return mid;
        if (A[mid] < x) {
            low = mid + 1;
        } else {
            high = mid -1;
        }  
    }
    return -1;
}
// We divide every time by 2, worst case time complexity is O(log(n))

int main() {

    int n = 1000000;
    int x = 7641356;
    int *A = malloc(n * sizeof(int));

    if (A == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        A[i] = i;
    }

    // Time linear search
    
    clock_t start_linear = clock();
    int res_linear = linear_search(A, n, x);
    clock_t end_linear = clock();
    double time_linear = (double)(end_linear - start_linear) / CLOCKS_PER_SEC;
    
    printf("Temps recherche linéaire    : %f secondes \n", time_linear);


    // Time jump search
    
    clock_t start_jump = clock();
    int res_jump = jump_search(A, n, x);
    clock_t end_jump = clock();
    double time_jump = (double)(end_jump - start_jump) / CLOCKS_PER_SEC;
    
    printf("Temps recherche par sauts    : %f secondes \n", time_jump);


    // Time binary search
    
    clock_t start_binary = clock();
    int res_binary = binary_search(A, n, x);
    clock_t end_binary = clock();
    double time_binary = (double)(end_binary - start_binary) / CLOCKS_PER_SEC;
    
    printf("Temps recherche dichotomie    : %f secondes \n", time_binary);

    free(A);
    // The sortedness verification increases every search algorithm by the same time, we could remove that time to only measure the time it took to search 
}