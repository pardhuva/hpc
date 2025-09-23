#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_data = 0;
int read_count = 0;

pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;    // protects read_count
pthread_mutex_t resource_lock = PTHREAD_MUTEX_INITIALIZER; // controls access to shared_data

void* reader(void* arg) {
    long id = (long)arg;
    while (1) {
        // Entry Section
        pthread_mutex_lock(&read_lock);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&resource_lock);  // first reader locks the resource
        }
        pthread_mutex_unlock(&read_lock);

        // Critical Section
        printf("Reader %ld reads shared_data = %d\n", id, shared_data);
        usleep(100000);  // simulate reading time

        // Exit Section
        pthread_mutex_lock(&read_lock);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&resource_lock);  // last reader unlocks the resource
        }
        pthread_mutex_unlock(&read_lock);

        usleep(100000);  // simulate time between reads
    }
    return NULL;
}

void* writer(void* arg) {
    long id = (long)arg;
    while (1) {
        pthread_mutex_lock(&resource_lock);

        shared_data++;
        printf("Writer %ld writes shared_data = %d\n", id, shared_data);

        pthread_mutex_unlock(&resource_lock);

        usleep(150000);  // simulate time between writes
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

//here you were maintaining a readcount mutex adn resource mutex so 
//here actually the resource lock is used for writers so when a writer acquires that lock no readers are allowed to read 
//so by readcount ,when the first reader comes he locks the resrouce signalling that some reader si presen t
//when the last reader tehn we unlock it ,
//for best synchronisation we use the lock only when that resource locking and unlocking 
//so when teh last reader unlocks the resource mutex then the writer can access it adn start writing blocking the other readers 
//as they try to acquire the resrouce first (first reader )
