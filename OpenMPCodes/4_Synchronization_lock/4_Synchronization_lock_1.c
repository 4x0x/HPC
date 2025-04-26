#include <stdio.h>
#include <omp.h>

int main() {
    omp_lock_t lock;
    omp_init_lock(&lock);

#pragma omp parallel for
    for (int i = 0; i < 5; i++) {
        omp_set_lock(&lock);
        printf("Thread %d handles i = %d\n", omp_get_thread_num(), i);
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    return 0;
}
