#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int is_sorted_ascending(int A[], int n) {
    if (n <= 1) return 1;
    int old = A[0];
    for (int i = 1; i<n; i++) {
        int new = A[i];
        if (new < old) {
            return 0;
        }
        old = new;
    }
    return 1;
}

void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void selection_sort(int A[], int n) {
    for (int i = 0; i<= (n-2); i++) {
        int min  = i;
        for (int j = (i+1); j<= (n-1); j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        swap_int(&A[i], &A[min]);
    }
}
// Worst case time complexity is O(n^2)

void insertion_sort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}
// Best case the array is nearly sorted in an ascending order, time complexity would be O(n)
// Worst case the array is sorted in a descending order, time complexity would be O(n*n)

void bubble_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                swap_int(&A[j], &A[j + 1]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
// Worst case time complexity is O(n^2)

void merge(int A[], int L[], int n_L, int R[], int n_R) {
    int i = 0, j = 0, k = 0;

    while (i < n_L && j < n_R) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }

    while (i < n_L) {
        A[k++] = L[i++];
    }

    while (j < n_R) {
        A[k++] = R[j++];
    }
}

void merge_sort(int A[], int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;

    int L[mid];
    int R[n - mid];

    for (int i = 0; i < mid; i++) {
        L[i] = A[i];
    }

    for (int i = mid; i < n; i++) {
        R[i - mid] = A[i];
    }

    merge_sort(L, mid);
    merge_sort(R, n - mid);

    merge(A, L, mid, R, n - mid);
}
// Time complexity is O(nlog(n)) in every cases

int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap_int(&A[i], &A[j]);
        }
    }
    swap_int(&A[i + 1], &A[high]);
    return i + 1; 
}

void quick_sort(int A[], int low, int high) {
    if (low < high) {
        int p = partition(A, low, high);

        quick_sort(A, low, p - 1);

        quick_sort(A, p + 1, high);
    }
}

// Best case time complexity would be O(nlog(n))
// Worst case time complexity would be O(n*n)

int main() {
    srand(time(NULL));

    int n = 20000;

    int *A = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));

    if (A == NULL || temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(A);
        free(temp);
        return 1;
    }

    // Fill array with random values
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000000;
    }

    // Time Selection Sort
    copy_array(A, temp, n);
    clock_t start_sel = clock();
    selection_sort(temp, n);
    clock_t end_sel = clock();
    double time_sel = (double)(end_sel - start_sel) / CLOCKS_PER_SEC;
    printf("Selection Sort time : %f seconds\n", time_sel);

    // Time Insertion Sort
    copy_array(A, temp, n);
    clock_t start_ins = clock();
    insertion_sort(temp, n);
    clock_t end_ins = clock();
    double time_ins = (double)(end_ins - start_ins) / CLOCKS_PER_SEC;
    printf("Insertion Sort time : %f seconds\n", time_ins);

    // Time Bubble Sort
    copy_array(A, temp, n);
    clock_t start_bub = clock();
    bubble_sort(temp, n);
    clock_t end_bub = clock();
    double time_bub = (double)(end_bub - start_bub) / CLOCKS_PER_SEC;
    printf("Bubble Sort time    : %f seconds\n", time_bub);

    // Time Merge Sort
    copy_array(A, temp, n);
    clock_t start_merge = clock();
    merge_sort(temp, n);
    clock_t end_merge = clock();
    double time_merge = (double)(end_merge - start_merge) / CLOCKS_PER_SEC;
    printf("Merge Sort time     : %f seconds\n", time_merge);

    // Time Quick Sort
    copy_array(A, temp, n);
    clock_t start_quick = clock();
    quick_sort(temp, 0, n - 1);
    clock_t end_quick = clock();
    double time_quick = (double)(end_quick - start_quick) / CLOCKS_PER_SEC;
    printf("Quick Sort time     : %f seconds\n", time_quick);

    free(A);
    free(temp);

    return 0;
}
/*
 * O(n log n) vs O(n^2) complexity:
 *    Merge Sort (0.004s) and Quick Sort (0.003s) are over 100x faster than
 *    O(n^2) algorithms, confirming the gap between quadratic 
 *    and log-linear time complexities
 *
 * O(n^2) algorithms comparison:
 *    - Bubble Sort (1.59s): Slowest due to continuous adjacent element swaps.
 *    - Selection Sort (0.62s): Faster because it performs at most n - 1 swaps.
 *    - Insertion Sort (0.35s): Most efficient O(n^2) algorithm because shifting elements is faster than performing full swaps.
 *
 * O(n log n) algorithms comparison:
 *    - Quick Sort (0.0031s) slightly beats Merge Sort (0.0042s) because it sorts in-place without the overhead of allocating and copying temporary arrays.
 */