#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    double start_time, end_time;

    // Without collapse
    start_time = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
#pragma omp atomic
            sum += i + j;
        }
    }

    end_time = omp_get_wtime();
    printf("Sum without collapse = %d\n", sum);
    printf("Time without collapse: %f seconds\n", end_time - start_time);

    // Reset sum
    sum = 0;

    // With collapse(2)
    start_time = omp_get_wtime();

#pragma omp parallel for collapse(2)
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
#pragma omp atomic
            sum += i + j;
        }
    }

    end_time = omp_get_wtime();
    printf("Sum with collapse = %d\n", sum);
    printf("Time with collapse: %f seconds\n", end_time - start_time);

    return 0;
}
