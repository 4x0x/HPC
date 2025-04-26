#include <stdio.h>
#include <omp.h>

int main() {
    int a = 0, b = 0;

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task depend(out:a)
            {
                printf("Task 1: setting a\n");
                a = 10;
            }

#pragma omp task depend(in:a) depend(out:b)
{
    printf("Task 2: using a, setting b\n");
    b = a + 5;
}

#pragma omp task depend(in:b)
{
    printf("Task 3: using b = %d\n", b);
}
        }
    }

    return 0;
}
