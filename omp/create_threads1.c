#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

 void main() {
     
    #pragma omp parallel num_threads(4)
    {
        printf("thread entered\n");
    }
    printf("%d\n ", omp_get_num_threads());

    #pragma omp parallel
    {
       printf("this is also executed\n");
    }
 }

 //here the num_threads() scope is only for that block means after that block only main thread.
 //num_threads(N) specifies the total number of threads in the team, including the main thread.
 //Inside the parallel block, all threads (including main) execute the block.
 //Therefore, the block is executed exactly 4 times, one for each thread.
 //what if you want the threads for all the blocks ??? create_threads2.c
//here for second construct two pritns because the default thread is 1 and the main thread is 1 
//even before you create the 4threads for the next construct they will not be there 
 