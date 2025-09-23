#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count =0;
int in=0;
int out=0;
int i=0;
    
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* producing() {
    
    while(1){
         pthread_mutex_lock(&lock);
         if(count<BUFFER_SIZE){
         buffer[in] = i;
         printf("Produced: %d at index %d\n", i, in);
         i++;
         in = (in+1)%BUFFER_SIZE;
         count++;
       }else{
          pthread_mutex_unlock(&lock);
          break;
       }
       pthread_mutex_unlock(&lock);
    }
    
}
void* consuming() {
   
    while(1){
       pthread_mutex_lock(&lock);
       if(count >0){
          int consumed = buffer[out];
            printf("Consumed: %d from index %d\n", consumed, out);
            out = (out+1)%BUFFER_SIZE;
            count--;   
       }else{
          pthread_mutex_unlock(&lock);
          break;
       }
       pthread_mutex_unlock(&lock);
    }
    
}
void main(){

    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer,NULL,producing,NULL);
    pthread_create(&consumer,NULL,consuming,NULL);

    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);

    return;
}

//here the shared are count -> what if consumer and producer read the count as 2 
//now producer produce nad count becomes 3 adn then consumer who read count as 2 he consume and it becomes 1 he rewrites
//that is because While doing the producer or consumer task, it reads the global variables before and stores them in its own local copy, so even if the producer updates before consumer, the consumer doesn’t know about it.
//in this we misses the count 
//that is why we use mutex  
//and next the shared are in and out so if two producers read  in at one time this might also leads to race condition so we use mutex 
//you might another doubt what if two producers read the in at the same time then one might have acquired the lock and do the producign and change the in 
//then what about the second thread which is waiting with the old in value wont it get updated ??
//actually lock do memory synchronisation so whenever you get the lock it does it it checks the memory for the updated values 
