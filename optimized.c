#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define THRESHOLD 16  // Threshold for switching to insertion sort

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);

    // Place pivot at high - 1
    swap(&arr[mid], &arr[high - 1]);
    return arr[high - 1];
}

int partition(int arr[], int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low;
    int j = high - 1;

    while (1) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i < j)
            swap(&arr[i], &arr[j]);
        else
            break;
    }

    swap(&arr[i], &arr[high - 1]);  // Restore pivot
    return i;
}

void quickSort(int arr[], int low, int high) {
    while (low < high) {
        if (high - low < THRESHOLD) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pi = partition(arr, low, high);
            if (pi - low < high - pi) {
                quickSort(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSort(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
}

int main() {
    int *arr = (int*)malloc(SIZE * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    clock_t start = clock();

    quickSort(arr, 0, SIZE - 1);

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Optimized QuickSort of %d elements took %.6f seconds.\n", SIZE, time_taken);

    free(arr);
    return 0;
}
