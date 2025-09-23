
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        printf("Reader %ld sees %d\n", (long)arg, shared_data);
        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
    return NULL;
}

void* writer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        shared_data++;
        printf("Writer %ld updated to %d\n", (long)arg, shared_data);
        pthread_mutex_unlock(&lock);
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

    return 0;
}

//here even for readers we apply locks so only one reader can read at a time but actually multiple  readers can read at a time as they wont modify 
//so if you take that mutex condition for readers to allwo mutiple readers then 
//if some writer was writing the shared variable some readers might read the previous values which is inconsistent data so we shoudl remove the mutex 
//we here code is correct but not parallel for multiple users we use rw

//here you were only either read or right only one at a time 
//but actually multiple readers can read 
