#include <zmq.h>

int main(void)
{
  int major, minor, patch;
  zmq_version(&major, &minor, &patch);
  printf("ZeroMQ v%d.%d.%d\n", major, minor, patch);
  return 0;
}
