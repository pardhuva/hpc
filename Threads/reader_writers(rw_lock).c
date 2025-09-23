#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader(void* arg) {
    long id = (long)arg;
    while (1) {
        pthread_rwlock_rdlock(&rwlock); // acquire read lock
        printf("Reader %ld reads shared_data = %d\n", id, shared_data);
        usleep(100000); // simulate reading
        pthread_rwlock_unlock(&rwlock); // release read lock
        usleep(100000);
    }
    return NULL;
}

void* writer(void* arg) {
    long id = (long)arg;
    while (1) {
        pthread_rwlock_wrlock(&rwlock); // acquire write lock
        shared_data++;
        printf("Writer %ld updates shared_data = %d\n", id, shared_data);
        usleep(150000); // simulate writing
        pthread_rwlock_unlock(&rwlock); // release write lock
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, w1;

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&w1, NULL, writer, (void*)1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

//pthread_rwlock_rdlock(&rwlock) - Multiple threads can acquire read lock simultaneously.
//pthread_rwlock_wrlock(&rwlock) - Writer gets exclusive access.Blocks if any readers or writers are active.
//pthread_rwlock_unlock(&rwlock) - release lock whether read or write 
//so these are internally manageble 
