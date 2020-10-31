/**********************************************************************************************************************
 * MIT License
 * Copyright (c) 2020 Utkarsh Bhatt
 * @About: Library to provide a logging process in the host program to easily generate cleaner logs.
 **********************************************************************************************************************/

#ifndef _E_LOGS_H_
#define _E_LOGS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>


#include "infra.h"

/*  Global Constants  */
#define LOG_STAMP_MAX_SIZE 256
#define LOG_MAX_SIZE 4096
#define LOG_MAX_FILENAME_SIZE 30

/*  Enumerations  */
typedef enum {
    info = 0,
    debug_low = 1,
    debug_med = 2,
    debug_high = 3,
    warn = 4,
    error = 5,
    fatal = 6
} LoggingLevel;

typedef enum {
    ddmmyyyy,
    mmddyyyy
} DateStyle;

/*  Structures  */
typedef struct {
    LoggingLevel level;
    const char* levelTag;
} LogVector;

/*  Global vars  */
// Vector table which contains the LogLevel -> LogLevelName relationship.
// TODO: Fix some structs showig (null);
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

// Logfile name dynamically generated for each session.
char *g_log_filename = NULL;

// Log ON/OFF
Bool *g_log_switch = NULL;

typedef struct {
    const char* function;
    const char* filename;
    const int   line;
} LogOrigin;

Status activateLogs()
{
    if (g_log_switch == NULL)
        return failure;

    int curr_state = (int)(*g_log_switch);
    *g_log_switch = True;

    // LOG_INFO("Activated Log Service: State(%d) -> State(%d)", curr_state, True);

    return success;
}

Status deactivateLogs()
{
    if (g_log_switch == NULL)
        return failure;

    // if (True == (int)(*g_log_switch))
    //     LOG_INFO("Deactivated Log Service: State(%d) -> State(%d)", True, False);

    *g_log_switch = False;

    return success;
}

Bool isLogActivated()
{
    if (g_log_switch == NULL)
        return False;

    return *g_log_switch;   // Switch State.
}

Status initLogModule(DateStyle date_style)
{
    g_log_filename = (char *)malloc((LOG_MAX_FILENAME_SIZE+1)*sizeof(char));
    g_log_switch = (Bool *)malloc(sizeof(Bool));
    if (g_log_filename == NULL || g_log_switch == NULL)
        return failure;

    memset(g_LogLevelTable, 0, LOG_MAX_FILENAME_SIZE);      // Clear String.
    memset(g_log_switch, True, sizeof(Bool));               // Set to True.
    
    time_t start_time = time(NULL);
    struct tm *time_info = localtime(&start_time);
    if (start_time == -1 || time_info == NULL)
        return failure;

    const char* log_filename_fmt = "[%02d-%02d-%04d](%02d-%02d-%02d).log";     // "Date::Time"
    
    int chnum;
    if (date_style == ddmmyyyy)
        chnum = snprintf(g_log_filename, LOG_MAX_FILENAME_SIZE, log_filename_fmt, time_info->tm_mday, time_info->tm_mon,
                 1900+time_info->tm_year, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    else if (date_style == mmddyyyy)
        chnum = snprintf(g_log_filename, LOG_MAX_FILENAME_SIZE, log_filename_fmt, time_info->tm_mon, time_info->tm_mday,
                 1900+time_info->tm_year, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    
    activateLogs();     // Activating log_switch;

    return success;
}

Status exitLogModule()
{
    // free log filename memory.
    free(g_log_filename);
    g_log_filename = NULL;

    // free log switch memory.
    free(g_log_switch);
    g_log_switch = NULL;
}

const char* getLogLevelName(LoggingLevel level)
{
    int num_levels = sizeof(g_LogLevelTable)/sizeof(LogVector);
    for (int i = 0; i < num_levels; i++) {
        if(level == g_LogLevelTable[i].level){
            // TODO: Remove this.
            printf("level(%d), Tag(%s)\n", g_LogLevelTable[i].level, g_LogLevelTable[i].levelTag);
            return g_LogLevelTable[i].levelTag;
        }
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
    // TODO: Remove this.
    printf("PASSED LEVEL IS %d\n", level);
    const char* log_tag = getLogLevelName(level);

    ret = fillLogStamp(&names, log_tag, &log_stamp);      // Step 1: Fill Stamp Info.
    if (success != ret)
        return failure;

    stamp_size = strlen(log_stamp);

    memcpy(log_bfr, log_stamp, stamp_size);                     // Step 2: Place the stamp to the log beginning.
    vsnprintf(log_bfr+stamp_size, LOG_MAX_SIZE, fmt, args);     // Step 3: Place the actual log after stamp.

    FILE* logFile = fopen(g_log_filename, "a");                 // Step 4: Open LogFile in append mode.
    if(logFile == NULL){
        // TODO: Remove this.
        printf("File pointer is NULL errno(%d)\n", errno);
        return failure;
    }

    fprintf(logFile, "%s\n", log_bfr);                          // Step 5: Fill log.
    fclose(logFile);                                            // Step 6: Close File.

    va_end(args);

    return success;
}

#define LOG_INIT(date_style)  do {          \
    initLogModule(date_style);              \
} while (0)

#define LOG_EXIT()  do {                    \
    exitLogModule();                        \
} while (0)

#define LOG_ACTIVATE()  do {                \
    activateLogs();                         \
} while (0)

#define LOG_DEACTIVATE()  do {              \
    deactivateLogs();                       \
} while (0)

#define LOG_INFO(msg, ...)  do {                \
    if (isLogActivated() == True) {             \
        LogOrigin name = {                      \
            .filename = __FILE__,               \
            .function = __func__,               \
            .line     = __LINE__                \
        };                                      \
        __elog(name, info, msg, ##__VA_ARGS__); \
    }                                           \
} while (0)

#define LOG_DBGL(msg, ...)  do {                        \
    if (isLogActivated() == True) {                     \
        LogOrigin name = {                              \
            .filename = __FILE__,                       \
            .function = __func__,                       \
            .line     = __LINE__                        \
        };                                              \
        __elog(name, debug_low, msg, ##__VA_ARGS__);    \
    }                                                   \
} while (0)

#define LOG_DBGM(msg, ...)  do {                        \
    if (isLogActivated() == True) {                     \
        LogOrigin name = {                              \
            .filename = __FILE__,                       \
            .function = __func__,                       \
            .line     = __LINE__                        \
        };                                              \
        __elog(name, debug_med, msg, ##__VA_ARGS__);    \
    }                                                   \
} while (0)

#define LOG_DBGH(msg, ...)  do {                        \
    if (isLogActivated() == True) {                     \
        LogOrigin name = {                              \
            .filename = __FILE__,                       \
            .function = __func__,                       \
            .line     = __LINE__                        \
        };                                              \
        __elog(name, debug_high, msg, ##__VA_ARGS__);   \
    }                                                   \
} while (0)

#define LOG_WARN(msg, ...)  do {                    \
    if (isLogActivated() == True) {                 \
        LogOrigin name = {                          \
            .filename = __FILE__,                   \
            .function = __func__,                   \
            .line     = __LINE__                    \
        };                                          \
        __elog(name, warn, msg, ##__VA_ARGS__);     \
    }                                               \
} while (0)

#define LOG_EROR(msg, ...)  do {                    \
    if (isLogActivated() == True) {                 \
        LogOrigin name = {                          \
            .filename = __FILE__,                   \
            .function = __func__,                   \
            .line     = __LINE__                    \
        };                                          \
        __elog(name, error, msg, ##__VA_ARGS__);    \
    }                                               \
} while (0)

#define LOG_FATL(msg, ...)  do {                \
    if (isLogActivated() == True) {             \
        LogOrigin name = {                      \
            .filename = __FILE__,               \
            .function = __func__,               \
            .line     = __LINE__                \
        };                                      \
    __elog(name, fatal, msg, ##__VA_ARGS__);    \
    }                                           \
} while (0)
// TODO: Fix log tag null error for INFO and DBG modes.
#endif /*  _E_LOGS_H_  */
