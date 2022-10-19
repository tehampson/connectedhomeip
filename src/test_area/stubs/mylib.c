//#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef unsigned int (*sleep_fn_t)(unsigned int seconds);
typedef int (*clock_gettime_fn_t)(clockid_t clk_id, struct timespec * tp);
typedef int (*gettimeofday_fn_t)(struct timeval * tv, void * tz);
typedef int (*clock_gettime_nsec_np_fn_t)(clockid_t clk_id);
typedef int (*mach_get_times_fn_t)(uint64_t * absolute_time, uint64_t * cont_time, struct timespec * tp);
typedef uint64_t (*mach_absolute_time_fn_t)(void);

int mach_absolute_time(void)
{
    static mach_absolute_time_fn_t orig_mach_absolute_time = NULL;

    printf("Intercepted mach_absolute_time\n");
    if (orig_mach_absolute_time == NULL)
    {
        orig_mach_absolute_time = (mach_absolute_time_fn_t) dlsym(RTLD_NEXT, "mach_absolute_time");
    }
    return orig_mach_absolute_time();
}

int mach_get_times(uint64_t * absolute_time, uint64_t * cont_time, struct timespec * tp)
{
    static mach_get_times_fn_t orig_mach_get_times = NULL;

    printf("Intercepted mach_get_times\n");
    if (orig_mach_get_times == NULL)
    {
        orig_mach_get_times = (mach_get_times_fn_t) dlsym(RTLD_NEXT, "mach_get_times");
    }
    return orig_mach_get_times(absolute_time, cont_time, tp);
}

#if 0
// This is called before main on darwin. The `dlsym` called causes a deadlock. Intercepting this properly is
// going to be important when calling `dispatch_walltime`. But for now we are going to ignore this since it
// doesn't help with actually queue any work to the dispatch work queue.
uint64_t clock_gettime_nsec_np(clockid_t clock_id)
{
    static clock_gettime_nsec_np_fn_t orig_clock_gettime_nsec_np = NULL;
    printf("Intercepted clock_gettime_nsec_np\n");
    if (orig_clock_gettime_nsec_np == NULL)
    {
        orig_clock_gettime_nsec_np = (clock_gettime_nsec_np_fn_t) dlsym(RTLD_NEXT, "clock_gettime_nsec_np");
    }
    return orig_clock_gettime_nsec_np(clock_id);
}
#endif

int clock_gettime(clockid_t clk_id, struct timespec * ts)
{
    static clock_gettime_fn_t orig_clock_gettime = NULL;
    printf("Intercepted clock_gettime\n");

    if (orig_clock_gettime == NULL)
    {
        orig_clock_gettime = (clock_gettime_fn_t) dlsym(RTLD_NEXT, "clock_gettime");
    }
    return orig_clock_gettime(clk_id, ts);
}

int gettimeofday(struct timeval * tv, void * tz)
{
    static gettimeofday_fn_t orig_gettimeofday = NULL;
    printf("Intercepted gettimeofday\n");

    if (orig_gettimeofday == NULL)
    {
        orig_gettimeofday = (gettimeofday_fn_t) dlsym(RTLD_NEXT, "gettimeofday");
    }
    return orig_gettimeofday(tv, tz);
}

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