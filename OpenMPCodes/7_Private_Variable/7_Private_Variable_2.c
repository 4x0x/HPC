#include <stdio.h>
#include <omp.h>

int main() {
    int shared_var = 50;  // Shared by all threads
    int private_var = 50;  // Will be private inside parallel region

#pragma omp parallel private(private_var) shared(shared_var)
    {
        private_var = omp_get_thread_num();  // Each thread has its own private_var
        shared_var += omp_get_thread_num();  // All threads modify the same shared_var

        printf("Thread %d: private_var = %d, shared_var = %d\n", omp_get_thread_num(), private_var, shared_var);
    }

    printf("After parallel region: shared_var = %d, private_var = %d\n", shared_var, private_var);
    return 0;
}
