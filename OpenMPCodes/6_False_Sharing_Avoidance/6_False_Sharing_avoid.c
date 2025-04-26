#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define PAD 8

int main() {
    static long counter[NUM_THREADS][PAD];
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        for (long i = 0; i < 100000000; i++) {
            counter[id][0]++;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        printf("counter[%d][0] = %ld \n", i, counter[i][0]);
    }

    return 0;
}
