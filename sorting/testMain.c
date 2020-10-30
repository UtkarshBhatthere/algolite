#include <stdio.h>
#include "ctrlflag.h"
#include "infra.h"
#include "timer.h"

// Sorting Libraries.
#include "bubblesort.h"
#include "selectsort.h"
#include "rec_bubblesort.h"
#include "insertionsort.h"

#if defined (__WIN32__)
    #include <windows.h>
#elif
    #include <unistd.h>
#endif


int main() {
    int sample_size = 10000;
    int arr[sample_size];
    clock_t *timepointStart, *timepointEnd;
    double timeElapsed;
    
    ifillRandom(arr, sample_size);

    // Check if the array is already sorted. Uncomment according to need.
    // printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, sample_size));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, sample_size));

    // printf("\n\n\n Input\n");
    // iprint_array(arr, sample_size);

    // Start the timer.
    createTimepoint(&timepointStart);

    // BubbleSort.
    // ibubblesort_inc(arr, sample_size);
    // ibubblesort_dec(arr, sample_size);

    // SelectionSort.
    // iselectsort_inc(arr, sample_size);
    // iselectsort_dec(arr, sample_size);

    // Recursive BubbleSort.
    // ibubblesort_inc_rec(arr, sample_size);
    // ibubblesort_dec_rec(arr, sample_size);

    // InsertionSort.
    // iInsertionsort_inc(arr, sample_size);
    iInsertionsort_dec(arr, sample_size);

    
    // End timer.
    createTimepoint(&timepointEnd);
    timeElapsedFor(timepointStart, timepointEnd, &timeElapsed);

    // Free timers.
    freeTimepoint(&timepointStart);
    freeTimepoint(&timepointEnd);

    // printf("\n\n\n Output\n");
    // iprint_array(arr, sample_size);
    
    // Check if the array is sorted after process. Uncomment according to need.
    // printf("is Sorted (inc): %d\n", (int)isSorted_inc(arr, sample_size));
    printf("is Sorted (dec): %d\n", (int)isSorted_dec(arr, sample_size));
    printf("Time elapsed in sorting is: %f", timeElapsed);
    return 0; 
}

