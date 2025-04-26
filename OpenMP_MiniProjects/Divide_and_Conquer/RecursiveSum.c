#include <stdio.h>
#include <omp.h>

int parallel_sum(int arr[], int start, int end) {
    if (start == end) {
        return arr[start];
    }

    int mid = (start + end) / 2;
    int left_sum = 0, right_sum = 0;

#pragma omp task shared(left_sum)
    left_sum = parallel_sum(arr, start, mid);

#pragma omp task shared(right_sum)
    right_sum = parallel_sum(arr, mid + 1, end);

#pragma omp taskwait
    return left_sum + right_sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int total = 0;

    double start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            total = parallel_sum(arr, 0, n - 1);
        }
    }

    double end = omp_get_wtime();

    printf("Sum of array = %d\n", total);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
