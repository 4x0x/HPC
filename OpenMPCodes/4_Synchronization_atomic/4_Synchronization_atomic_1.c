#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

#pragma omp parallel for
    for (int i = 0; i < 5; i++) {
#pragma omp atomic
        sum += i;
    }

    printf("Final sum = %d\n", sum);
    return 0;
}
