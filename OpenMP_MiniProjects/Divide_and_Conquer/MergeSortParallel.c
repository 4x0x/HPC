#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Merge two sorted halves
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copy data
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Merge temp arrays
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Recursive Parallel Merge Sort
void parallel_merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

#pragma omp task shared(arr)
        parallel_merge_sort(arr, l, m);

#pragma omp task shared(arr)
        parallel_merge_sort(arr, m + 1, r);

#pragma omp taskwait
        merge(arr, l, m, r);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7, 4, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    double start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            parallel_merge_sort(arr, 0, n - 1);
        }
    }

    double end = omp_get_wtime();

    // Print sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
