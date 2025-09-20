#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
     
    int sum = 0;
    double start_time,end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(4)
    {
        
        printf("Thread %d before barrier\n", omp_get_thread_num());

        #pragma omp barrier  // all threads wait here
  
        printf("Thread %d after barrier\n", omp_get_thread_num());
    }

    end_time = omp_get_wtime();

    printf("Total time taken is %f\n", end_time - start_time);

    return 0;
 }
//Makes all threads wait at a point until everyone reaches the barrier.
//Ensures that no thread proceeds beyond this point until all threads have finished the preceding work.
