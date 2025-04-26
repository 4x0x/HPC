#include <stdio.h>
#include <omp.h>

int arr[2];  // Only 2 integers, close together in memory

int main() {
    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        for (int i = 0; i < 1000000; i++) {
            arr[id]++;  // Each thread modifies arr[0] or arr[1]
        }
    }
    printf("arr[0] = %d, arr[1] = %d\n", arr[0], arr[1]);
    return 0;
}

