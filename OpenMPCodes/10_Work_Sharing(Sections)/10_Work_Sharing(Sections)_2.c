#include <stdio.h>
#include <omp.h>

void taskA() { printf("Task A by thread %d\n", omp_get_thread_num()); }
void taskB() { printf("Task B by thread %d\n", omp_get_thread_num()); }

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        taskA();
        
        #pragma omp section
        taskB();
    }
    return 0;
}