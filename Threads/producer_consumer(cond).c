#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;
int item = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_full = PTHREAD_COND_INITIALIZER;   // Used when buffer is full
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;  // Used when buffer is empty

void* producing(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);

        while (count == BUFFER_SIZE) {
            // Buffer full → wait for space
            pthread_cond_wait(&cond_full, &lock);
        }

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        item++;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&cond_empty);  // Wake up consumer if waiting
        pthread_mutex_unlock(&lock);

        usleep(100000); // Optional: slow down for readability
    }
    return NULL;
}

void* consuming(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);

        while (count == 0) {
            // Buffer empty → wait for data
            pthread_cond_wait(&cond_empty, &lock);
        }

        int consumed = buffer[out];
        printf("Consumed: %d from index %d\n", consumed, out);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&cond_full);  // Wake up producer if waiting
        pthread_mutex_unlock(&lock);

        usleep(150000); // Optional: slow down for readability
    }
    return NULL;
}

int main() {
    pthread_t producer, consumer;

    pthread_create(&producer, NULL, producing, NULL);
    pthread_create(&consumer, NULL, consuming, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}

//What's the benefit of using condition variables over the previous mutex-only version?
//Isn't it still kind of "waiting" before producing/consuming?
//without condition variables -> if a producer checking whether the buffer is full or not after getting the lock  
// if not then it checks in loop whether it is available or not which leads to many cpu cycles waste that is why we use condition variables 
//so if it is full then it will keep the producer to sleep adn wake him up when  it get the empty signal from the consumer 
//this applies even to consumer who keep on checking whether the buffer is empty or not sleeps until he get the isfull signal from the producer 

//but here we only check for the buffer but why are we not checking for locks dont two threads keep on checking if the lock is available or not 
//actually that is what trylock does keeps on chekcing but actual mutex we use it automatically keep the other to sleep when not available adn wake him up when available 

//here you might get infinite iterations you produce and consume many times 
//but it before mutex approach only fixed amount even there si while(1) because whenever thread sees full then it will immediately exit as the buffer is full 
//not like condtion where even its full you will wait for consumer making it empty adn then produce not like mutex wher eyou exit 

//now here first when the buffer is full then the produces wait with full condition until the consumer sends the full signal to remove from the wait who is waiting with full 
//same way when the consumer is waiting wiht empty then it waits for signal empty which is sent by the producer to unlock the wait threads with empty wait condition 


