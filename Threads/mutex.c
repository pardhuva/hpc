#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static int turn = 0;

void*f(){
    pthread_mutex_lock(&lock);
    if(turn == 0){
        turn =1;
    }else{
        turn = 10;
    }
    pthread_mutex_unlock(&lock);
}

void main() {
    pthread_t t1;
    pthread_t t2;
    
    pthread_create(&t1,NULL,f,NULL);
    pthread_create(&t2,NULL,f,NULL);
    
     pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%d ",turn);
}

//here if you dont keep the mutex then both might check that if condition at the same time adn they might change that turn oly to 1 
//so actulaly there will be only function code that is shared among all the threads only the arguments might differ for each thread means the local variables 
//so all the threads execute the function concurrently until you want some line only to execute in a ordered way we use mutex locks 
