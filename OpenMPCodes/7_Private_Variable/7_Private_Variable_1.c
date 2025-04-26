#include <stdio.h>
#include <omp.h>

int main() {
    int x = 5;

#pragma omp parallel private(x)
    {
        x = omp_get_thread_num();  // Each thread sets its own x
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);
    }

    return 0;
}
