/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Selection sort Algorithm for sorting Numbers.
 * @Brief: Selection sort is an in-place comparison sorting algorithm. It has an O(n2) time complexity, which makes it
 * inefficient on large lists, and generally performs worse than the similar insertion sort. Selection sort is noted
 * for its simplicity and has performance advantages over more complicated algorithms in certain situations,
 * particularly where auxiliary memory is limited.
 * @Read: https://en.wikipedia.org/wiki/Selection_sort
 **********************************************************************************************************************/

#ifndef _SELECTSORT_H_
#define _SELECTSORT_H_

#include "infra.h"

void iselectsort_inc(int* unsrt_bfr, const long size)
{

    for (int i = 0; i < size; i++) {
        int smallest_index = i;
        for (int j = i + 1; j < size; j++) {
            if (unsrt_bfr[smallest_index] > unsrt_bfr[j]) {
                smallest_index = j;
            }
        }

        // Swap the ith smallest number with the number at ith position.
        iswap(unsrt_bfr+smallest_index, unsrt_bfr+i);
    }
}

void iselectsort_dec(int* unsrt_bfr, const long size)
{
    for (int i = 0; i < size; i++) {
        int largest_index = i;
        for (int j = i + 1; j < size; j++) {
            if (unsrt_bfr[largest_index] < unsrt_bfr[j]) {
                largest_index = j;
            }
        }

        // Swap the ith largest number with the number at ith position.
        iswap(unsrt_bfr+largest_index, unsrt_bfr+i);
    }
}



#endif // _SELECTSORT_H_