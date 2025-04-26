#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel for ordered
    for (int i = 0; i < 5; i++) {
#pragma omp ordered
        printf("Ordered print: i = %d by thread %d\n", i, omp_get_thread_num());
    }

    return 0;
}
