#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int a[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

#pragma omp parallel for
    for (i = 0; i < 15; i++) {
        a[i] = a[i] * 2;
        printf("Thread %d doubled a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
    }

    return 0;
}
