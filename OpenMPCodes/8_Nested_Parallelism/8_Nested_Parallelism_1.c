#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_nested(1);  // Enable nested parallelism

#pragma omp parallel num_threads(2)
    {
        printf("Outer thread %d\n", omp_get_thread_num());

#pragma omp parallel num_threads(2)
        {
            printf("  Inner thread %d (inside outer thread %d)\n", omp_get_thread_num(), omp_get_ancestor_thread_num(1));
        }
    }

    return 0;
}
