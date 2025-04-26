#include <stdio.h>
#include <omp.h>

void do_work(int task_num) {
    printf("Task %d is working by thread %d\n", task_num, omp_get_thread_num());
}

int main() {
#pragma omp parallel
    {
#pragma omp single
        {
            for (int i = 1; i <= 15; i++) {
#pragma omp task
                do_work(i);
            }
        }
    }
    return 0;
}
