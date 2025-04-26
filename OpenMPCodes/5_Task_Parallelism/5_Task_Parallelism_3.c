#include <stdio.h>
#include <omp.h>

void do_task(int option) {
    switch(option) {
        case 1:
            printf("Loading data (thread %d)\n", omp_get_thread_num());
        break;
        case 2:
            printf("Processing data (thread %d)\n", omp_get_thread_num());
        break;
        case 3:
            printf("Saving results (thread %d)\n", omp_get_thread_num());
        break;
        default:
            printf("Unknown option (thread %d)\n", omp_get_thread_num());
    }
}

int main() {
    int option;
    printf("Choose an option (1 = Load, 2 = Process, 3 = Save): ");
    scanf("%d", &option);

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            do_task(option);
        }
    }

    return 0;
}
