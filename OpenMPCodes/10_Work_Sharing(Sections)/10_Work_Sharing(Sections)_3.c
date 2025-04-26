#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0, product = 1;

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                for (int i = 1; i <= 5; i++) sum += i;
                printf("Sum calculated by thread %d: %d\n", omp_get_thread_num(), sum);
            }

#pragma omp section
{
    for (int i = 1; i <= 5; i++) product *= i;
    printf("Product calculated by thread %d: %d\n", omp_get_thread_num(), product);
}
        }
    }
    return 0;
}
