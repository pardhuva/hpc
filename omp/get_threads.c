#include <stdio.h>
#include <omp.h>

int main() {
    printf("Before parallel region: only main thread %d of %d\n",omp_get_thread_num(),omp_get_num_threads());

    #pragma omp parallel num_threads(3)
    {
        printf("Inside parallel region: Thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    printf("After parallel region: only main thread %d of %d \n",omp_get_thread_num(), omp_get_num_threads());
    return 0;
}

//omp_get_thread_num() returns the id of the thread 
//omp_get_num_threads() returns the number of threads 