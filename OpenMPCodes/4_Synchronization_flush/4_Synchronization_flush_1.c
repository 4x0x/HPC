#include <stdio.h>
#include <omp.h>

int main() {
    int flag = 0;

#pragma omp parallel sections
    {
#pragma omp section
        {
            flag = 1;
#pragma omp flush(flag)  // Make sure other threads see updated flag
        }

#pragma omp section
{
    while (flag == 0) {
#pragma omp flush(flag)  // Keep checking latest flag
    }
    printf("Flag updated, thread %d continues\n", omp_get_thread_num());
}
    }

    return 0;
}
