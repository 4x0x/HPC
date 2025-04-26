#include <stdio.h>
#include <omp.h>

int arr[16];  // Bigger array to spread elements apart

int main() {
    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        for (int i = 0; i < 1000000; i++) {
            arr[id * 8]++;  // Access arr[0] and arr[8] (far apart)
        }
    }
    printf("arr[0] = %d, arr[8] = %d\n", arr[0], arr[8]);
    return 0;
}

