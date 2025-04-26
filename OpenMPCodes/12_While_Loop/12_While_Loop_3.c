#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;
    int limit = 6;

#pragma omp parallel
    {
        while (1) {
            int work;

#pragma omp critical
            {
                if (counter < limit) {
                    work = counter;
                    counter++;
                } else {
                    work = -1;
                }
            }

            if (work == -1) break; // No more work

            printf("Thread %d processes item %d\n", omp_get_thread_num(), work);
        }
    }
    return 0;
}
