#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(4)
    {
        int counter = 0; // Private for each thread
        while (counter < 3) {
            printf("Thread %d counter = %d\n", omp_get_thread_num(), counter);
            counter++;
        }
    }
    return 0;
}
