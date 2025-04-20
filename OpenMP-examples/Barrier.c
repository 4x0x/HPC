#include <stdio.h>
#include <omp.h>
int main() {
    int tid;
    int y, z;
    int x = 0;
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        y = 25;
        if (tid == 0) {
            y = 10;
        } else {
            z = 89 + tid + 4;
        }
        printf("before the barrier y: %d, tid: %d\n", y, tid);
#pragma omp barrier
        printf("after the barrier y: %d, tid: %d\n", y, tid);

if (tid == 1) {
    x = x + y;
    printf("value %d\n", x);
}
    }
    return 0;
}
