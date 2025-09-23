#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2 + 1);

        int first = (id % 2 == 0) ? right : left;
        int second = (id % 2 == 0) ? left : right;

        if (pthread_mutex_trylock(&forks[first]) == 0) {
            if (pthread_mutex_trylock(&forks[second]) == 0) {
                // Eat
                printf("Philosopher %d is eating with forks %d and %d.\n", id, first, second);
                sleep(rand() % 2 + 1);
                pthread_mutex_unlock(&forks[second]);
            }
            pthread_mutex_unlock(&forks[first]);
        }

        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

//here we make like we give indices to the philosophers and then 
//if the philosopher index is odd then he try to pick left first adn then right 
//if even then he try to pick right first adn then left 
//in this way we prevent deadlock 

//there are other approaches where semaphore approach we we allow counting semaphore is used 
//means we allow only (n-1) philosophers to do so we are making sure atleast one will be succeed in eating 

