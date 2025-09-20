#include <stdio.h>
#include <omp.h>

int main() {
    double start_time, end_time;

    start_time = omp_get_wtime();  // Record start time

    
    end_time = omp_get_wtime();    // Record end time

    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
