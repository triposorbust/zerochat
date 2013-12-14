#ifndef __ZEROCHAT_H__
#define __ZEROCHAT_H__

#ifndef __ZMQ_H__
#define __ZMQ_H__
#include <zmq.h>
#endif

#ifndef __ASSERT_H__
#define __ASSERT_H__
#include <assert.h>
#endif

#ifndef __PTHREAD_H__
#define __PTHREAD_H__
#include <pthread.h>
#endif

#ifndef __STDLIB_H__
#define __STDLIB_H__
#include <stdlib.h>
#endif

#ifndef __STRING_H__
#define __STRING_H__
#include <string.h>
#endif

static char *
s_recv (void *socket) {
  char buffer [2048];
  int size = zmq_recv (socket, buffer, 2048, 0);
  if (size == -1)
    return NULL;
  if (size > 2048)
    size = 2048;
  buffer [size] = 0;
  return strdup (buffer);
}

static int
s_send (void *socket, char *string) {
  int size = zmq_send (socket, string, strlen (string), 0);
  return size;
}

#endif
