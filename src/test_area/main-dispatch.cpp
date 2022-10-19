#include <stdio.h>
#include <dispatch/dispatch.h>

int foobar = 0;

int main() {
  dispatch_queue_t serialQueue;
  serialQueue = dispatch_queue_create("cl.martoq.log_queue", DISPATCH_QUEUE_SERIAL);

  dispatch_source_t timerSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, DISPATCH_TIMER_STRICT, serialQueue);
  dispatch_source_set_timer(
            timerSource, dispatch_walltime(nullptr, static_cast<int64_t>(30 * NSEC_PER_MSEC)),
            DISPATCH_TIME_FOREVER, 2 * NSEC_PER_MSEC);

        dispatch_source_set_event_handler(timerSource, ^{
            foobar = 1;
            printf("Timer Done!\n");
            dispatch_source_cancel(timerSource);
            dispatch_release(timerSource);

			
        });
        dispatch_resume(timerSource);

  dispatch_source_t timerSource2 = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, DISPATCH_TIMER_STRICT, serialQueue);
  dispatch_source_set_timer(
            timerSource2, dispatch_walltime(nullptr, static_cast<int64_t>(10 * NSEC_PER_MSEC)),
            DISPATCH_TIME_FOREVER, 2 * NSEC_PER_MSEC);

        dispatch_source_set_event_handler(timerSource2, ^{
            foobar = 1;
            printf("Timer Done 2!\n");
            dispatch_source_cancel(timerSource2);
            dispatch_release(timerSource2);

			
        });
        dispatch_resume(timerSource2);

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


   printf("Hello, World!\n");
   dispatch_sync(serialQueue, ^{
       printf("inside sync done!\n");
   });
   sleep(5);
   printf("sync done foobar=%d!\n", foobar);
   sleep(3);
   printf("done done!\n");
   return 0;
}
