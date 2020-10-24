/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Bubblesort Algorithm for sorting Numbers.
 * @Brief: Bubble sort, sometimes referred to as sinking sort, is a simple sorting algorithm that repeatedly steps
 * through the list, compares adjacent elements and swaps them if they are in the wrong order. The pass through the
 * list is repeated until the list is sorted. The algorithm, which is a comparison sort, is named for the way smaller
 * or larger elements "bubble" to the top of the list.
 * @Read: https://en.wikipedia.org/wiki/Bubble_sort
 **********************************************************************************************************************/

#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include "infra.h"

void ibubblesort_inc(int* unsrt_bfr, const long size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
           if (unsrt_bfr[j] > unsrt_bfr[j+1]) {
                #ifdef __INFO
                    printf("Swapped %d with %d\n", unsrt_bfr[j+1], unsrt_bfr[j]);
                #endif
                iswap(unsrt_bfr+j, unsrt_bfr+j+1);
           }
        }
    }
}

void ibubblesort_dec(int* unsrt_bfr, const long size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size -i -1; j++) {
           if (unsrt_bfr[j] < unsrt_bfr[j+1]) {
                #ifdef __INFO
                    printf("Swapped %d with %d\n", unsrt_bfr[j+1], unsrt_bfr[j]);
                #endif
                iswap(unsrt_bfr+j, unsrt_bfr+j+1);
           }
        }
        
    }
}

#endif /* _BUBBLESORT_H_ */