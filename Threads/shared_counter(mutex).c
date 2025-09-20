#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int counter = 1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count() {
    for(int i=0; i<5; i++){
        pthread_mutex_lock(&lock);
        counter = counter + 1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;

    pthread_create(&p1, NULL, count, NULL);
    pthread_create(&p2, NULL, count, NULL);

    // Wait for threads to finish first
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("The counter is %d\n", counter);

    return 0;
}

//here we are maintaining mutex to ensure at once only one thread modifies once 
//in this example of counter actually for independent large tasks threads are useful 
//it is useful in banks concepts 
