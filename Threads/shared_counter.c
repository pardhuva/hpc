
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

static int counter = 1;
void* count() {
    for(int i=0;i<5;i++){
        counter = counter+1;
    }
}
void main() {
    pthread_t p1,p2;
    
    pthread_create(&p1,NULL,count,NULL);
    pthread_create(&p2,NULL,count,NULL);
    
    printf("The counter is %d , ",counter);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
}

//here two threads to modify the shared variable counter 1 
//here two threads are created its not confirm that the first can execute first 
//race condition exists here because they are modifying the same variable counter 
//so both might read the counter 1 at first and they might update the same variable same time 
//so p1 reads 1 and p2 reads 1 
//p1 increments nad update counter to 2 and then the p2 increments and it also has 2 it overwrite the 2 
//in this way there is no synchronisation 
//so the output will be 6 instead of 11 
