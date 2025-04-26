#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;
    
    #pragma omp parallel
    {
        #pragma omp critical
        {
            counter++;
            printf("Thread %d: counter = %d\n", 
                   omp_get_thread_num(), counter);
        }
    }
    
    printf("Final counter = %d\n", counter);
    return 0;
}
