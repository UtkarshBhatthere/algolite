/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Insertion Sort Algorithm for sorting Numbers.
 * @Brief: In computer science, merge sort (also commonly spelled mergesort) is an efficient, general-purpose, 
 * comparison-based sorting algorithm. Most implementations produce a stable sort, which means that the order of equal 
 * elements is the same in the input and output. Merge sort is a divide and conquer algorithm that was invented by John
 * von Neumann in 1945
 * @Read: https://en.wikipedia.org/wiki/Merge_sort
 **********************************************************************************************************************/

#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include "infra.h"

void __mergesrt_inc(int* unsrt_bfr, const long left, const long right);
void __mergesrt_dec(int* unsrt_bfr, const long left, const long right);
void __merge_inc(int* unsrt_bfr, const long left, const long middle, const long right);
void __merge_dec(int* unsrt_bfr, const long left, const long middle, const long right);

/*  APIs  */
void iMergesort_inc(int* unsrt_bfr, const long size)
{
    __mergesrt_inc(unsrt_bfr, 0, size-1);
}

void iMergesort_dec(int* unsrt_bfr, const long size)
{
    __mergesrt_dec(unsrt_bfr, 0, size-1);
}

/*  Internal APIs  */
void __mergesrt_inc(int* unsrt_bfr, const long left, const long right)
{
    // Recursion Breaking condition.
    if (left < right) {
        // Overflow protected middle calculation.
        long middle = left + (right - left)/2;

        __mergesrt_inc(unsrt_bfr, left, middle);        // Sort First Half.
        __mergesrt_inc(unsrt_bfr, middle+1, right);     // Sort Second Half.
        __merge_inc(unsrt_bfr, left, middle, right);        // Merge the two sorted halves.
    }

}

void __mergesrt_dec(int* unsrt_bfr, const long left, const long right)
{
    if (left < right) {
        long middle = left + (right - left)/2;

        __mergesrt_dec(unsrt_bfr, left, middle);
        __mergesrt_dec(unsrt_bfr, middle+1, right);
        __merge_dec(unsrt_bfr, left, middle, right);
    }
}

void __merge_inc(int* unsrt_bfr, const long left, const long middle, const long right)
{
    long len1 = middle-left+1;       // Inclusive of middle.
    long len2 = right-middle;        // Exclusive of middle.

    int fHalf[len1];
    int sHalf[len2];

    // Copy first half of the Sorted Bfr.
    for (int i = 0; i < len1; i++) {
        fHalf[i] = unsrt_bfr[left+i];
    }

    // Copy second half of the sorted Bfr.
    for (int i = 0; i < len2; i++) {
        sHalf[i] = unsrt_bfr[middle+1+i];
    }

    // Counters for all sub arrays.
    int i = 0, j = 0, k = left;

    // Fill the mair array in ascending order.
    while(i < len1 && j < len2) {
        if (fHalf[i] <= sHalf[j]) {
            unsrt_bfr[k++] = fHalf[i++];
        } else {
            unsrt_bfr[k++] = sHalf[j++];
        }
    }

    // Fill remaining elements from left sub array.
    while (i < len1)
    {
        unsrt_bfr[k++] = fHalf[i++];
    }

    // Fill remaining elements from right sub array.
    while (j < len2) {
        unsrt_bfr[k++] = sHalf[j++];
    }
}

void __merge_dec(int* unsrt_bfr, const long left, const long middle, const long right)
{
    long len1 = middle-left+1;
    long len2 = right-middle;

    int fHalf[len1];
    int sHalf[len2];

    for (int i = 0; i < len1; i++) {
        fHalf[i] = unsrt_bfr[left+i];
    }

    for (int i = 0; i < len2; i++) {
        sHalf[i] = unsrt_bfr[middle+1+i];
    }

    int i=0, j=0, k=left;

    while (i < len1 && j < len2)
    {
        if (fHalf[i] > sHalf[j]) {
            unsrt_bfr[k++] = fHalf[i++];
        } else
        {
            unsrt_bfr[k++] = sHalf[j++];
        }
    }
    
    while (i < len1)
    {
        unsrt_bfr[k++] = fHalf[i++];
    }
    
    while (j < len2)
    {
        unsrt_bfr[k++] = sHalf[j++];
    }

}

#endif /*   _MERGE_SORT_H_   */