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
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 2 + 1); // Thinking for 1-2 seconds

        printf("Philosopher %d is hungry.\n", id);

        // Try to pick up left fork
        if (pthread_mutex_trylock(&forks[left]) == 0) {
            printf("Philosopher %d picked up left fork %d\n", id, left);

            // Try to pick up right fork
            if (pthread_mutex_trylock(&forks[right]) == 0) {
                printf("Philosopher %d picked up right fork %d\n", id, right);

                // Eat
                printf("Philosopher %d is eating.\n", id);
                sleep(rand() % 2 + 1); // Eating for 1-2 seconds

                // Put down right fork
                pthread_mutex_unlock(&forks[right]);
                printf("Philosopher %d put down right fork %d\n", id, right);
            }

            // Put down left fork (either after eating or if right fork not available)
            pthread_mutex_unlock(&forks[left]);
            printf("Philosopher %d put down left fork %d\n", id, left);
        }

        // If couldn't eat, think again (back to start)
        sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize all forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (optional in simulation)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes (won't be reached here)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

//so threads -> for each dining philosopher as he has to do some task 
//5 chopsticks so lock for each chopstick 
//so whenver he gets the left then try for right if not then leave left too, or else take those and eat and return both the chopsticks release locks of left and right 
//here thread(philosopher) try to pick left first and then if try for right 
//but this might lead to deadlock whatif alll threads took the left 
//that is why the optimal is given 
