#include <stdio.h>
#include <unistd.h>

typedef unsigned int (*sleep_fn_t)(unsigned int seconds);

int main(int argc, char *argv[])
{
  printf("Hello World, please wait 2s\n");
  sleep(2);
  printf("Thank you for waiting 2s\n");
  return 0;
}