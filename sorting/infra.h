/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Infrastructure Code essential throughout the library.
 **********************************************************************************************************************/
#ifndef _INFRA_H_
#define _INFRA_H_

#include <stdlib.h>
#include <time.h>

typedef enum {
    true = 1,
    True = true,
    false = !true,
    False = false
} Bool;

typedef enum {
    success = 1,
    failure = !success
} Status;

// Usage iswap(&a, &b) -> where a and b are two integers.
void iswap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void ifillRandom(int* bfr, const long size)
{
    // Seeding the pseudo-random number generator.
    srand(time(0));

    for (int i = 0; i < size; i++) {
        bfr[i] = rand();
    }
}

Bool isSorted_inc(int* unsrt_bfr, const long size)
{
    Bool flag = true;

    for (int i =0; i < size - 1; i++) {
        if (unsrt_bfr[i] > unsrt_bfr[i+1]) {
            flag = false;
            
            #ifdef __INFO
                printf("Fault at %d\n", i);
            #endif
        }

        // if(flag == false)    // Break at first fault.
        //     break;
    }

    return flag;
}

Bool isSorted_dec(int* unsrt_bfr, const long size)
{
    Bool flag = true;

    for (int i =0; i < size - 1; i++) {
        if (unsrt_bfr[i] < unsrt_bfr[i+1]) {
            flag = false;

            #ifdef __INFO
                printf("Fault at %d\n", i);
            #endif
        }

        // if(flag == false)    // Break at first fault.
        //     break;
    }

    return flag;
}

void iprint_array(int* unsrt_bfr, const long size)
{
    for (int i = 0; i < size; i++) {
        printf("%dth : %d\n", i, unsrt_bfr[i]);
    }
}

#endif /* _INFRA_H_ */