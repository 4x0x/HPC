#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello from thread %d of %d\n", 
               thread_id, omp_get_num_threads());
    }
    return 0;
}
