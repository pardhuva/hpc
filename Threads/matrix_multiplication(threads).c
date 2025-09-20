#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct to pass arguments to thread
typedef struct {
    int row;
    int (*matrix)[3];
    int* vector;
    int* result;
} ThreadArgs;

// Thread function
void* function(void* arg) {
    ThreadArgs* args = (ThreadArgs*) arg;
    int i = args->row;

    for (int j = 0; j < 3; j++) {
        args->result[i] += args->matrix[i][j] * args->vector[j];
    }

    pthread_exit(NULL);
}

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int vector[3] = {3, 2, 1};
    int y[3] = {0};  // Result vector

    pthread_t thread1, thread2, thread3;

    // Allocate and initialize arguments for each thread
    ThreadArgs* args1 = malloc(sizeof(ThreadArgs));
    args1->row = 0; args1->matrix = matrix; args1->vector = vector; args1->result = y;
    pthread_create(&thread1, NULL, function, (void*) args1);

    ThreadArgs* args2 = malloc(sizeof(ThreadArgs));
    args2->row = 1; args2->matrix = matrix; args2->vector = vector; args2->result = y;
    pthread_create(&thread2, NULL, function, (void*) args2);

    ThreadArgs* args3 = malloc(sizeof(ThreadArgs));
    args3->row = 2; args3->matrix = matrix; args3->vector = vector; args3->result = y;
    pthread_create(&thread3, NULL, function, (void*) args3);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Print result
    printf("Result vector y: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", y[i]);
    }
    printf("\n");

    // Free allocated memory
    free(args1);
    free(args2);
    free(args3);

    return 0;
}

//here we are sending the matrix and vector copies to all the threads seperately 
//here so each thread updates each row 