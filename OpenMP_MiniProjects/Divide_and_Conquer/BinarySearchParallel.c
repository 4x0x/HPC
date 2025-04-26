#include <stdio.h>
#include <omp.h>

int parallel_binary_search(int arr[], int start, int end, int target) {
    if (start > end) return -1;

    int mid = (start + end) / 2;

    if (arr[mid] == target) return mid;

    int result = -1;

#pragma omp task shared(result)
    {
        if (arr[mid] > target) {
            result = parallel_binary_search(arr, start, mid - 1, target);
        }
    }

#pragma omp task shared(result)
{
    if (arr[mid] < target) {
        result = parallel_binary_search(arr, mid + 1, end, target);
    }
}

#pragma omp taskwait
    return result;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 14;
    int found = -1;

    double start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            found = parallel_binary_search(arr, 0, n - 1, target);
        }
    }

    double end = omp_get_wtime();

    if (found != -1)
        printf("Element found at index %d\n", found);
    else
        printf("Element not found\n");

    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
