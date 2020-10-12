#include <stdio.h>
#include "bubblesort.h"
#include "infra.h"

int main() {
    int arr[100];
    for (int i = 100; i > 0; i--) {
        arr[100 - i] = 101 - i;
    }

    // Uncomment if printing array is required.
    // iprint_array(arr, 100);

    // Check if the array is already sorted. Uncomment according to need.
    // printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, 100));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, 100));

    // Increasing BubbleSort.
    // ibubblesort_inc(arr, 100);
    ibubblesort_dec(arr, 100);

    // Uncomment if printing array is required.
    // iprint_array(arr, 100);
    
    // Check if the array is sorted after process. Uncomment according to need.
    // printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, 100));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, 100));
    return 0; 
}

