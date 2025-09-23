#include<stdio.h>
#include<omp.h>

int main() {

    omp_set_num_threads(3);

    #pragma omp for 

    for(int i=0;i<2;i++){
        printf("thread is running by %d \n",omp_get_thread_num());
    }
    
    #pragma omp parallel 
    for(int i=0;i<2;i++){
        printf("entire for loop is executed by each thread\n");
    }

    #pragma omp parallel 
    {
        #pragma omp for 
        
            for(int i=0;i<2;i++){
                printf("this is parallilzed\n");
            }
        
    }
    return 0;
}

//omp parallel then this executes the down block by each thread 
//ompp for if you add that for then it parallizes the for 
//after omp for dont keep the flower brackets no block 

