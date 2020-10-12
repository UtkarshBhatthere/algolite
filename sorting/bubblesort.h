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
    for (int i = 0; i <= size; i++) {
        bool wasSwapped = false;
        int swap_index;
        for (int j = 0; j <= size; j++) {
            if (unsrt_bfr[i] > unsrt_bfr[j]) {
                swap_index = j;
                #ifdef __DEBUG
                    printf("Swapped %d with %d\n", unsrt_bfr[i], unsrt_bfr[j]);
                #endif
                wasSwapped = true;
            }
        }
        if (wasSwapped == false){
            #ifdef __DEBUG
                printf("Not Swapped \n");
            #endif
            break;
        } else if (wasSwapped == true) {
            iswap(unsrt_bfr + i, unsrt_bfr + swap_index);
        }
    }
}

void ibubblesort_dec(int* unsrt_bfr, const long size) {
    for (int i = 0; i <= size; i++) {
        bool wasSwapped = false;
        int swap_index;
        for (int j = 0; j <= size; j++) {
            if (unsrt_bfr[i] < unsrt_bfr[j]) {
                swap_index = j;
                #ifdef __DEBUG
                    printf("Swapped %d with %d\n", unsrt_bfr[i], unsrt_bfr[j]);
                #endif
                wasSwapped = true;
            }
        }
        if (wasSwapped == false){
            #ifdef __DEBUG
                printf("Not Swapped \n");
            #endif
            break;
        } else if (wasSwapped == true) {
            iswap(unsrt_bfr + i, unsrt_bfr + swap_index);
        }
    }
}

#endif /* _BUBBLESORT_H_ */