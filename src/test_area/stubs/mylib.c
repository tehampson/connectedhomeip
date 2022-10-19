//#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int (*sleep_fn_t)(unsigned int seconds);

unsigned int sleep(unsigned int seconds)
{
    static sleep_fn_t original_sleep = NULL;
    if (original_sleep == NULL)
    {
        original_sleep = (sleep_fn_t) dlsym(RTLD_NEXT, "sleep");
    }
    printf("We have successfully intercepted sleep\n");
    return original_sleep(seconds);
}