#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main() {
     
    int sum = 0;

    #pragma omp parallel for
    for(int i=0; i<100; i++) {
        sum += i;  // Race condition! multiple threads updating sum at same time
    }
    printf("%d",sum);
    return 0;
 }

 //actually there whenever parallel is given all the threads execute parallely without thinking about other as they are independen t
 //in the above case if two threads execute them parallely they both change the same sum at time this might give you wrong ans 
 //so we use synchonisation methods 