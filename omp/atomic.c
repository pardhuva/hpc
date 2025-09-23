#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
     
    int sum = 0;
    double start_time,end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel for
    for(int i=0; i<100; i++) {
       #pragma omp atomic
       {
           sum += i;  
       }
    }
    printf("%d",sum);
    end_time = omp_get_wtime();

    printf("Total time taken is %f\n", end_time - start_time);
    
    return 0;
 }

 //atomic functions same as critical but atomic provides you lock only for one instruction 
 //it is faster than critical 
 //is only one instruction to be locked or might cause race condition then use atomic 
 //if more than one then use critical 
 //the real big difference occurs when you have more threads or more iterations 

 