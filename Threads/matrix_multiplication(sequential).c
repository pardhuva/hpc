
#include <stdio.h>
#include <stdlib.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int vector[3] = {3, 2, 1};
    int y[3] = {0};  

   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            y[i] += matrix[i][j] * vector[j];
        }
    }

    
    for (int i = 0; i < 3; i++) {
        printf("%d ", y[i]);
    }

    printf("\n");

    return 0;
}

