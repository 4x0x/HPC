#include <stdio.h>
#include <omp.h>

void subtask(int id) {
#pragma omp parallel num_threads(2)
    {
        printf("    Subtask %d by thread %d\n", id, omp_get_thread_num());
    }
}

int main() {
    omp_set_nested(1);

#pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        printf("Team thread %d starting subtask...\n", tid);
        subtask(tid);
    }

    return 0;
}
