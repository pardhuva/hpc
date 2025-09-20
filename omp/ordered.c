#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
     
    int sum = 0;
    double start_time,end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for ordered
    for (int i = 0; i < 5; i++) {
        #pragma omp ordered
        printf("%d ", i);  // printed in order 0 1 2 3 4
    }

    end_time = omp_get_wtime();

    printf("Total time taken is %f\n", end_time - start_time);

    return 0;
 }
//Ensures that iterations of a parallel loop are executed in sequential order inside the loop.
//Useful when you need ordered output or dependent operations inside a loop.
//Only works inside a parallel for loop with ordered specified in the loop directive.
//Prevents race conditions for sequential dependency, but slows down execution because threads may wait to preserve order.
