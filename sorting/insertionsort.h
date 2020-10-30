/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Insertion Sort Algorithm for sorting Numbers.
 * @Brief: Insertion sort is a simple sorting algorithm that builds the final sorted array (or list) one item at a 
 * time. It is much less efficient on large lists than more advanced algorithms such as quicksort, heapsort, etc.
 * @Read: https://en.wikipedia.org/wiki/Insertion_sort
 **********************************************************************************************************************/

#ifndef _INSERTION_SORT_H_
#define _INSERTION_SORT_H_

#include "infra.h"

// TODO: Change all method signatures using CamelCase.
void iInsertionsort_inc(int* unsrt_bfr, const long size)
{
    for (int i = 1; i < size; i++) {

        int curr_val = unsrt_bfr[i];
        int curr_indx = i;

        while(curr_indx > 0 && unsrt_bfr[curr_indx-1] > curr_val){
            iCopy(unsrt_bfr+curr_indx-1, unsrt_bfr+curr_indx);
            curr_indx--;
        }

        unsrt_bfr[curr_indx] = curr_val;
    }
}

void iInsertionsort_dec(int* unsrt_bfr, const long size)
{
    for (int i = 1; i < size; i++) {

        int curr_val = unsrt_bfr[i];
        int curr_indx = i;

        while(curr_indx > 0 && unsrt_bfr[curr_indx-1] < curr_val){
            iCopy(unsrt_bfr+curr_indx-1, unsrt_bfr+curr_indx);
            curr_indx--;
        }

        unsrt_bfr[curr_indx] = curr_val;
    }
}

#endif /*  _INSERTION_SORT_H_  */