#include <stdio.h>
#include <pthread.h>

#define N 3

int matrix[N][N] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
};
int vector[N] = {3,2,1};
int result[N] = {0};  // Shared result

typedef struct {
    int row;  // Row to compute
} ThreadArg;

void* computeRow(void* arg) {
    ThreadArg* t = (ThreadArg*) arg;
    int r = t->row;
    for (int j = 0; j < N; j++) {
        result[r] += matrix[r][j] * vector[j];
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    ThreadArg args[N];

    for (int i = 0; i < N; i++) {
        args[i].row = i;
        pthread_create(&threads[i], NULL, computeRow, &args[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}

//here like before where you send every copy of the matrix and vector 
//as the threads were just reading the matrix and vetor no change right so no race condition as they are not modifign the shared space 
//so we make it global as they were just modifying the result vector that too on unique indices 