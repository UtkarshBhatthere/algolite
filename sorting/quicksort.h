/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Quick Sort Algorithm for sorting Numbers.
 * @Brief: Quicksort (sometimes called partition-exchange sort) is an efficient sorting algorithm. Developed by British
 * computer scientist Tony Hoare in 1959[1] and published in 1961,[2] it is still a commonly used algorithm for sorting.
 * When implemented well, it can be about two or three times faster than its main competitors, merge sort and heapsort.
 * @Read: https://en.wikipedia.org/wiki/Quicksort
 **********************************************************************************************************************/

#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include "infra.h"

void __partition_inc(int* unsrt_bfr, const long low, const long high);
void __partition_dec(int* unsrt_bfr, const long low, const long high);


void iQuickSort_inc(int* unsrt_bfr, const long size)
{
    __partition_inc(unsrt_bfr, 0, size-1);      // size-1 is the index of last element.
}

void iQuickSort_dec(int* unsrt_bfr, const long size)
{
    __partition_dec(unsrt_bfr, 0, size-1);      // size-1 is the index of last element.
}

void __partition_inc(int* unsrt_bfr, const long low, const long high)
{
    long swap_index = low - 1;
    int pivot = unsrt_bfr[high];    // Right pivot algo.

    if (low >= high)
        return;

    for (int i = low; i <= high; i++) {
        if (unsrt_bfr[i] <= pivot) {
            swap_index++;
            iswap(unsrt_bfr+swap_index, unsrt_bfr+i);
        }
    }

    __partition_inc(unsrt_bfr, low, swap_index-1);
    __partition_inc(unsrt_bfr, swap_index+1, high);
}

void __partition_dec(int* unsrt_bfr, const long low, const long high)
{
    long swap_index = low - 1;
    int pivot = unsrt_bfr[high];

    if (low >= high)
        return;

    for (long i = low; i <= high; i++)
    {
        if (unsrt_bfr[i] >= pivot) {
            swap_index++;
            iswap(unsrt_bfr+swap_index, unsrt_bfr+i);
        }
    }
    
    __partition_dec(unsrt_bfr, low, swap_index-1);
    __partition_dec(unsrt_bfr, swap_index+1, high);
}

#endif /*   _QUICK_SORT_H_   */