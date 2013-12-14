#ifndef __ZEROCHAT_H__
#include "ZEROCHAT.H"
#endif

static char BUFFER [2048];

static char IDENTITY [128];
static char PUSHTO [128];
static char SUBTO [128];

void *subscribe (void *context)
{
  void *subscriber = zmq_socket (context, ZMQ_SUB);
  int rc = zmq_connect (subscriber, SUBTO);
  assert (rc == 0);
  rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "", 0);
  assert (rc == 0);

  while (1) {
    char *string = s_recv (subscriber);
    printf ("%s\n", string);
    free (string);
  }

  zmq_close (subscriber);
  pthread_exit (NULL);
}

void *push (void *context)
{
  void *push = zmq_socket (context, ZMQ_PUSH);
  zmq_connect (push, PUSHTO);

  while (1) {
    sprintf (BUFFER, "%s: ", IDENTITY);
    gets (& BUFFER [strlen ((const char *) IDENTITY) + 2]);
    s_send (push, BUFFER);
  }

  zmq_close (push);
  pthread_exit (NULL);
}

void setstring (char *buffer, int size, const char *prompt)
{
  int i = 0;
  char c;
  printf ("%s", prompt);
  for (;;) {
    c = getchar();
    if (c == '\n' || i >= size-1)
      break;
    buffer [i++] = c;
  }
}

int main (void)
{
  void *context = zmq_ctx_new ();
  setstring(IDENTITY, 128, "Welcome! Please choose a username: ");
  setstring(PUSHTO, 128, "Publication socket: ");
  setstring(SUBTO, 128, "Subscription socket: ");

  int rc;
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_t subscribe_thread, push_thread;
  rc = pthread_create (&subscribe_thread, &attr, &subscribe, context);
  assert (rc == 0);
  rc = pthread_create (&push_thread, &attr, &push, context);
  assert (rc == 0);

  void *status;
  rc = pthread_join (subscribe_thread, &status);
  assert(rc == 0);
  rc = pthread_join (push_thread, &status);
  assert(rc == 0);

  pthread_attr_destroy (&attr);
  zmq_ctx_destroy (context);
  pthread_exit (NULL);
}
