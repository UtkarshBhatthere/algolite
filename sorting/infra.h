/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Infrastructure Code essential throughout the library.
 **********************************************************************************************************************/
#ifndef _INFRA_H_
#define _INFRA_H_

typedef enum {
    true = 1,
    True = true,
    false = !true,
    False = false
} bool;

// Usage iswap(&a, &b) -> where a and b are two integers.
void iswap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

bool isSorted_inc(int* unsrt_bfr, const long size) {
    bool flag = true;

    for (int i =0; i < size - 1; i++) {
        if (unsrt_bfr[i] > unsrt_bfr[i+1]) {
            flag = false;
        }

        if(flag == false)
            break;
    }

    return flag;
}

bool isSorted_dec(int* unsrt_bfr, const long size) {
    bool flag = true;

    for (int i =0; i < size - 1; i++) {
        if (unsrt_bfr[i] < unsrt_bfr[i+1]) {
            flag = false;
        }

        if(flag == false)
            break;
    }

    return flag;
}

void iprint_array(int* unsrt_bfr, const long size) {
    for (int i = 0; i < size; i++) {
        printf("%dth : %d\n", i, unsrt_bfr[i]);
    }
}

#endif /* _INFRA_H_ */