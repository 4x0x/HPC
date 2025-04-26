#include <stdio.h>
#include <omp.h>

int main() {
    int a=0, b=0;
    
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task depend(out:a)
        { a = 1; printf("Task A\n"); }
        
        #pragma omp task depend(out:b)
        { b = 2; printf("Task B\n"); }
        
        #pragma omp task depend(in:a,b)
        { printf("Task C: a+b = %d\n", a+b); }
    }
    return 0;
}