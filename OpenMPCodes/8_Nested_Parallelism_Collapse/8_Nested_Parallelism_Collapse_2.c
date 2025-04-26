#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel for collapse(3)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                printf("Thread %d (i=%d, j=%d, k=%d)\n", omp_get_thread_num(), i, j, k);
            }
        }
    }
    return 0;
}
