#include <stdio.h>
#include "ctrlflag.h"
#include "infra.h"
#include "timer.h"
#include "elogs.h"

void doit(void)
{
    
    LOG_INFO("Hello %s, this is log number %d", "World", 1);
    LOG_DBGL("Hello %s, this is log number %d", "World", 2);
    LOG_DBGM("Hello %s, this is log number %d", "World", 3);
    LOG_DBGH("Hello %s, this is log number %d", "World", 4);
    LOG_WARN("Hello %s, this is log number %d", "World", 5);
    LOG_EROR("Hello %s, this is log number %d", "World", 6);
    LOG_FATL("Hello %s, this is log number %d", "World", 7);
}

int main(void)
{
    doit();
}