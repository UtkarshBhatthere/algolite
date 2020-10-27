/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Library to provide a logging process in the host program to easily generate cleaner logs.
 **********************************************************************************************************************/

#ifndef _ELOGS_H_
#define _E_LOGS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "infra.h"

#define LOG_STAMP_MAX_SIZE 256
#define LOG_MAX_SIZE 4096

typedef enum {
    info,
    debug_low,
    debug_med,
    debug_high,
    warn,
    error,
    fatal
} LoggingLevel;

typedef struct {
    LoggingLevel level;
    const char* levelTag;
} LogVector;

LogVector g_LogLevelTable[] =
{
    info, "INFO",
    debug_low, "DBGL",
    debug_med, "DBGM",
    debug_high, "DBGH",
    warn, "WARN",
    error, "EROR",
    fatal, "FATL"
};

typedef struct {
    const char* function;
    const char* filename;
    const int   line;
} LogOrigin;

#define LOG_INFO(msg, ...)  do {            \
    LogOrigin name = {                      \
        .filename = __FILE__,               \
        .function = __func__,               \
        .line     = __LINE__                \
    };                                      \
    __elog(name, info, msg, ##__VA_ARGS__); \
    } while (0)                             \

#define LOG_DBGL(msg, ...)  do {                    \
    LogOrigin name = {                              \
        .filename = __FILE__,                       \
        .function = __func__,                       \
        .line     = __LINE__                        \
    };                                              \
    __elog(name, debug_low, msg, ##__VA_ARGS__);    \
    } while (0)                                     \

#define LOG_DBGM(msg, ...)  do {                    \
    LogOrigin name = {                              \
        .filename = __FILE__,                       \
        .function = __func__,                       \
        .line     = __LINE__                        \
    };                                              \
    __elog(name, debug_med, msg, ##__VA_ARGS__);    \
    } while (0)                                     \

#define LOG_DBGH(msg, ...)  do {                    \
    LogOrigin name = {                              \
        .filename = __FILE__,                       \
        .function = __func__,                       \
        .line     = __LINE__                        \
    };                                              \
    __elog(name, debug_high, msg, ##__VA_ARGS__);   \
    } while (0)                                     \

#define LOG_WARN(msg, ...)  do {            \
    LogOrigin name = {                      \
        .filename = __FILE__,               \
        .function = __func__,               \
        .line     = __LINE__                \
    };                                      \
    __elog(name, warn, msg, ##__VA_ARGS__); \
    } while (0)                             \

#define LOG_EROR(msg, ...)  do {                 \
    LogOrigin name = {                          \
        .filename = __FILE__,                   \
        .function = __func__,                   \
        .line     = __LINE__                    \
    };                                          \
    __elog(name, error, msg, ##__VA_ARGS__);    \
    } while (0)                                 \

#define LOG_FATL(msg, ...)  do {                \
    LogOrigin name = {                          \
        .filename = __FILE__,                   \
        .function = __func__,                   \
        .line     = __LINE__                    \
    };                                          \
    __elog(name, fatal, msg, ##__VA_ARGS__);    \
    } while (0)                                 \

const char* getLogLevelName(LoggingLevel level)
{
    int num_levels = sizeof(g_LogLevelTable)/sizeof(LogVector);
    for (int i = 0; i < num_levels; i++) {
        if(level == g_LogLevelTable[i].level)
            return g_LogLevelTable[i].levelTag;
    }

    return g_LogLevelTable[0].levelTag;
}

Status fillLogStamp(LogOrigin *names, const char* log_level, char **stamp_bfr)
{
    char* log_stamp_fmt = "[%02d.%02d.%02d][%s][%s in %s:%d] -> ";
    *stamp_bfr = (char *)malloc((LOG_STAMP_MAX_SIZE+1)* sizeof(char));

    if (NULL == *stamp_bfr)
        return failure;

    memset(*stamp_bfr, 0, LOG_STAMP_MAX_SIZE+1);

    time_t curr_time = time(NULL);
    struct tm *time_info = localtime(&curr_time);
    
    int chnum = snprintf(*stamp_bfr, LOG_STAMP_MAX_SIZE, log_stamp_fmt, time_info->tm_hour, time_info->tm_min,
                         time_info->tm_sec, log_level, names->function, names->filename+2, names->line);   // +2 to skip the ./ in filename.
    
    if(chnum < 1)
        return failure;

    return success;
}

Status __elog(LogOrigin names, LoggingLevel level, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *log_stamp = NULL;
    int stamp_size;
    char log_bfr[4096] = "\0";

    Status ret = failure;
    const char* log_tag = getLogLevelName(level);

    ret = fillLogStamp(&names, log_tag, &log_stamp);      // Step 1: Fill Stamp Info.
    if (success != ret)
        return failure;

    stamp_size = strlen(log_stamp);

    memcpy(log_bfr, log_stamp, stamp_size);                     // Step 2: Place the stamp to the log beginning.
    vsnprintf(log_bfr+stamp_size, LOG_MAX_SIZE, fmt, args);     // Step 3: Place the actual log after stamp.

    printf("%s\n", log_bfr);

    va_end(args);

    return success;
}
// TODO: Implement a way to dump the logs to a file.
#endif /*  _E_LOGS_H_  */
