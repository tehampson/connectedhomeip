#include <stdio.h>
#include <sys/time.h>
#include <dispatch/dispatch.h>

int foobar = 0;

void AddTimer(dispatch_queue_t serialQueue, int timeMs)
{
  dispatch_source_t timerSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, DISPATCH_TIMER_STRICT, serialQueue);
  dispatch_source_set_timer(
      timerSource, dispatch_walltime(nullptr, static_cast<int64_t>(timeMs * NSEC_PER_MSEC)),
      DISPATCH_TIME_FOREVER, 2 * NSEC_PER_MSEC);

  dispatch_source_set_event_handler(timerSource, ^{
      foobar = 1;
      printf("Timer waiting for %dms Done!\n", timeMs);
      dispatch_source_cancel(timerSource);
      dispatch_release(timerSource);
  });
  dispatch_resume(timerSource);
}

int main() {
#if 0
  struct timeval start, end;
  gettimeofday(&start, NULL);
#endif
  dispatch_queue_t serialQueue = dispatch_queue_create("cl.martoq.log_queue", DISPATCH_QUEUE_SERIAL);

  printf("Hello, World!\n");
  AddTimer(serialQueue, 500);

  sleep(2);
  printf("sync done foobar=%d!\n", foobar);

#if 0
  dispatch_async(serialQueue, ^{
      printf("Start 1\n");
      sleep(2);
      printf("Done 1st\n");
  });
  
  dispatch_async(serialQueue, ^{
      printf("Start 2\n");
      sleep(2);
      printf("Done 2nd\n");
  });


  dispatch_sync(serialQueue, ^{
      printf("inside sync done!\n");
  });
  //sleep(5);
  printf("sync done foobar=%d!\n", foobar);
  sleep(3);
  gettimeofday(&end, NULL);
  printf("done done. Took total %ld!\n", ((end.tv_sec * 1000000 + end.tv_usec)
               - (start.tv_sec * 1000000 + start.tv_usec)));
#endif
  return 0;
}
