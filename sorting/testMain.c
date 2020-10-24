#include <stdio.h>
#include "ctrlflag.h"
#include "infra.h"
#include "timer.h"

// Sorting Libraries.
#include "bubblesort.h"
#include "selectsort.h"
#include "rec_bubblesort.h"


int main() {
    int arr[1000];
    clock_t *timepoint;
    double timeElapsed;
    
    ifillRandom(arr, 1000);

    // Check if the array is already sorted. Uncomment according to need.
    printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, 1000));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, 1000));

    // Start the timer.
    createTimepoint(&timepoint);

    // BubbleSort.
    // ibubblesort_inc(arr, 1000);
    ibubblesort_dec(arr, 1000);

    // SelectionSort.
    iselectsort_inc(arr, 1000);
    // iselectsort_dec(arr, 1000);

    // Recursive BubbleSort.
    // ibubblesort_inc_rec(arr, 1000);
    ibubblesort_dec_rec(arr, 1000);

    // End timer.
    endTimerFine(timepoint, &timeElapsed);

    #ifdef __DEBUG
        iprint_array(arr, 1000);
    #endif
    
    // Check if the array is sorted after process. Uncomment according to need.
    // printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, 1000));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, 1000));
    printf("Time elapsed in sorting is: %f", timeElapsed);
    return 0; 
}

