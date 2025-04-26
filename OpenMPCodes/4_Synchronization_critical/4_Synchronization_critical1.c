#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < 50; i++) {
    #pragma omp critical
        {
            sum += i;
            printf("i now  = %d , done by thread %d \n",i,omp_get_thread_num());
        }
    }
    
    printf("total sum = %d\n", sum);
    return 0;
}
