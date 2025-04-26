#include <stdio.h>
#include <omp.h>
#define N 100

int main() {
    double sum = 0.0;
    
    #pragma omp parallel for reduction(+:sum)
    for(int i=1; i<=N; i++) {
        sum += 1.0/i;
    }
    
    printf("sum = %f\n", sum);
    return 0;
}
