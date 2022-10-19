#if 0
#include <mach/mach_time.h>
#include <mach/clock.h>
#endif

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef unsigned int (*sleep_fn_t)(unsigned int seconds);

int main(int argc, char *argv[])
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  printf("tp.tv_sec: %ld\n", tp.tv_sec);
  printf("tp.tv_nsec: %ld\n", tp.tv_nsec);


  uint64_t absolute_time = 0;
  uint64_t cont_time =0;
  struct timespec tp2;

  //mach_get_times(&absolute_time, &cont_time, &tp2);

  //absolute_time = mach_absolute_time();
  //printf("absolute_time = %" PRIu64 "\n", absolute_time);

  //clock_gettime_nsec_np(CLOCK_MONOTONIC);

  struct timeval start, end;
  gettimeofday(&start, NULL);
  printf("Hello World, please wait 2s\n");
  sleep(2);
  printf("Thank you for waiting 2s\n");
  gettimeofday(&end, NULL);
  printf("Took total %ld!\n", ((end.tv_sec * 1000000 + end.tv_usec)
		 - (start.tv_sec * 1000000 + start.tv_usec)));
  return 0;
}