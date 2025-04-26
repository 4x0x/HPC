#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Hello from section 1 by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Hello from section 2 by thread %d\n", omp_get_thread_num());
            }
        }
    }
    return 0;
}
