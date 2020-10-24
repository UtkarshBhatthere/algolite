
/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Library to calculate the time elapsed between operations.
 **********************************************************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

#include "infra.h"

/**************************************************************************************************
 * @name:   createTimepoint
 * @brief:  Populates the passed in double pointer with the with the current CPU tick count.
 * @param:  start: Dbl Ptr to allocate and populate timepoint.
**************************************************************************************************/
status createTimepoint(clock_t **start)
{
    *start = (clock_t *)malloc(sizeof(clock_t));
    if(*start == NULL)
        return failure;
    
    **start = clock();   // Get current CPU ticks for starting point.
    if(**start == -1)
        return failure;

    return success;
}

/**************************************************************************************************
 * @name:   endTimerCoarse
 * @brief:  Calculates the coarse difference b/w current timem and passed in timepoint.
 * @param:  start: Ptr to calculate time difference, timeElapsed: Ptr to populate.
**************************************************************************************************/
status endTimerCoarse(clock_t *start, uint32_t *timeElapsed)
{
    clock_t end;
    double intermediateTimeDifference;

    end = clock();  // Get current CPU ticks for ending point.
    if(end == -1)
        return failure;

    intermediateTimeDifference = (end - *start)/CLOCKS_PER_SEC;
    *timeElapsed = (uint32_t)intermediateTimeDifference;

    return success;
}

/**************************************************************************************************
 * @name:   endTimerFine
 * @brief:  Calculates the fine difference b/w current timem and passed in timepoint.
 * @param:  start: Ptr to calculate time difference, timeElapsed: Ptr to populate.
**************************************************************************************************/
status endTimerFine(clock_t *start, double *timeElapsed)
{
    clock_t end;

    end = clock();  // Get current CPU ticks for ending point.
    if(end == -1)
        return failure;
    
    *timeElapsed = (end - *start)/CLOCKS_PER_SEC;

    return success;
}
#endif /*  _TIMER_H_  */
