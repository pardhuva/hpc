#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define BUFFER_SIZE 5

void main(){

    int buffer[BUFFER_SIZE];
    int in =0;
    int out =0;
    int items;

    for(int i=0;i<=10;i++){

        if(items <BUFFER_SIZE){
            buffer[in] = i;
            printf("Produced: %d at index %d\n", i, in);
            in = (in+1)%BUFFER_SIZE;
            items++;
        }
        if(items>0){
            int consumed = buffer[out];
            printf("Consumed: %d from index %d\n", consumed, out);
            out = (out+1)%BUFFER_SIZE;
            items--;
        }
    }

}

//here its like sequential but here we kind of right after the producer produces we are letting the consumer to consume it 
//but actually there is no need to be like that because the producer can produce multiple items at once and the consumer can consume them later when want 
//so we have to make the producers and consumers independent 
