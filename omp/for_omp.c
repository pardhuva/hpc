#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
     
    double start_time,end_time;

    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for(int i=0;i<10;i++)
    {
        printf("thread entered\n");
    }
    end_time = omp_get_wtime();

    printf("Total time taken is %f\n", end_time - start_time);
    return 0;
 }

 //here it takes without using for in the clause Total time taken is 0.000289 -> here you were parallelising the for loop to print once 
//if you use for in clause omp paralell for Total time taken is 0.000140 -> you are executing the for loop for eahc thread entirely 
