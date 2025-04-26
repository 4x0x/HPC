#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;
    int target = 10;

#pragma omp parallel
    {
        while (1) {
            int local_counter;

#pragma omp atomic capture
            local_counter = counter++;

            if (local_counter >= target) break;

            printf("Thread %d handled item %d\n", omp_get_thread_num(), local_counter);
        }
    }
    return 0;
}
