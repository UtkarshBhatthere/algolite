#include <stdio.h>
#include "ctrlflag.h"
#include "infra.h"
#include "timer.h"
#include "elogs.h"

void doit(void)
{
    LOG_INIT(ddmmyyyy);

    LOG_INFO("Easy Logs module is working -> %d", 1);
    LOG_DBGL("Low level debug logging is working -> %d", 2);
    LOG_DBGM("Med level debug logging is working -> %d", 3);
    LOG_DBGH("High level debug logging is working -> %d", 4);
    LOG_WARN("Warn logging is working -> %d", 5);
    LOG_EROR("Error logging is working -> %d", 6);
    LOG_FATL("Fatal logging is working -> %d", 7);

    LOG_DEACTIVATE();

    LOG_INFO("This shouldn't be in logs -> %d", 0);

    LOG_ACTIVATE();

    LOG_INFO("This should be in logs -> %d", 8);

    LOG_EXIT();
}

int main(void)
{
    doit();
}