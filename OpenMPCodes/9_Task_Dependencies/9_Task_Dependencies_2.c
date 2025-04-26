#include <stdio.h>
#include <omp.h>

int main() {
    int x = 0;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(out:x)
            {
                printf("Task 1: setting x\n");
                x = 42;
            }

#pragma omp task depend(in:x)
{
    printf("Task 2: using x = %d\n", x);
}
        }
    }

    return 0;
}
