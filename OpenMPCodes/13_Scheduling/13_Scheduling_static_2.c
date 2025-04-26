#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

#pragma omp parallel for schedule(static,2) reduction(+:sum)
    for (int i = 1; i <= 16; i++) {
        printf("Thread %d adds %d\n", omp_get_thread_num(), i);
        sum += i;
    }

    printf("Final sum (static, chunk=2) = %d\n", sum);
    return 0;
}
