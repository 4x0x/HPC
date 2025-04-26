#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_nested(1);

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < 2; i++) {
        printf("Outer loop iteration %d by thread %d\n", i, omp_get_thread_num());

#pragma omp parallel num_threads(2)
        {
            printf("  Inner work for iteration %d by thread %d\n", i, omp_get_thread_num());
        }
    }

    return 0;
}
