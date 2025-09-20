#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

 void main() {
     omp_set_num_threads(4);

    #pragma omp parallel
    {
        printf("thread entered\n");
    }
     printf("%d\n ", omp_get_num_threads());
    #pragma omp parallel
    {
       printf("this is also executed\n");
    }
    
 }

 //here when you use set_num_threads here 4 threads are created along with the main thread 
 //then 4 threads execute that parallel construct of first block 
 //then when teh block ends then all teh other threads terminate only main thread remains 
 //then for get it prints 1 giving you main thread remains 
 //then again when you create a parallel construct execute 
 //now again 4 threads which are set before will execute not like create_thread1 where it is scope only for one block 
 //then again after this block completion they terminate 

 //so basically if we use set then the number of threads by defautl changes when you call  another block of construct 

 