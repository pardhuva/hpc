#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main() {
    #pragma omp parallel 
    {
        printf("thread entered  this section\n");
    }
}
//so actually here you were not creating number of threads so default threads will be created 
//there is also main thread so whenever ther is construct omp parallel then openmp team forms including main thread 
//all the threads execute that construct region only the inside after  } all the thread exits only the main thread exists 
