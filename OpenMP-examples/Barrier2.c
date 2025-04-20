#include <stdio.h>
#include <omp.h>
int main() {
    int sharedCounter = 0;
#pragma omp parallel num_threads(4)
    {
        // Using atomic
#pragma omp atomic
        sharedCounter++;
    }
    // Using critical
#pragma omp critical
{
    sharedCounter++;
}
    printf("Final shared counter value: %d\n",
    sharedCounter);
    return 0;
}