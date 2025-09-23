#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int total;
} Barrier;

Barrier barrier;

void barrier_init(Barrier* b, int total) {
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->cond, NULL);
    b->count = 0;
    b->total = total;
}

void barrier_wait(Barrier* b) {
    pthread_mutex_lock(&b->mutex);
    b->count++;
    if (b->count == b->total) {
        b->count = 0;  // Reset for reuse
        pthread_cond_broadcast(&b->cond);
    } else {
        pthread_cond_wait(&b->cond, &b->mutex);
    }
    pthread_mutex_unlock(&b->mutex);
}

void* worker(void* arg) {
    long id = (long)arg;
    printf("Thread %ld is working before the barrier\n", id);
    sleep(rand() % 3);  // Simulate some work

    barrier_wait(&barrier);  // Synchronization point

    printf("Thread %ld passed the barrier\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    barrier_init(&barrier, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)(long)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

//so here you start the barrier so you cond_wait until all the threads reached
//that is done by comparing the count(number of threads reched hte barrier) and total(total number of threads)
//when all reached then you broadcast for those who are waiting to reach the barrier 
