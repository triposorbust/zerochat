#ifndef __ZEROCHAT_H__
#include "ZEROCHAT.H"
#endif

void *publish (void *context)
{
  void *publisher = zmq_socket (context, ZMQ_PUB);
  void *pulley = zmq_socket (context, ZMQ_PAIR);

  int rc = zmq_bind (publisher, "tcp://*:5556");
  assert (rc == 0);
  rc = zmq_bind (publisher, "ipc://messenger.ipc");
  assert (rc == 0);
  rc = zmq_bind (pulley, "inproc://crosstalk");
  assert (rc == 0);

  while (1) {
    char *string = s_recv (pulley);
    s_send (publisher, string);
  }

  zmq_close (pulley);
  zmq_close (publisher);
  pthread_exit (NULL);
}

void *receive (void *context)
{
  void *receiver = zmq_socket (context, ZMQ_PULL);
  void *pushey = zmq_socket (context, ZMQ_PAIR);

  int rc = zmq_bind (receiver, "tcp://*:5558");
  rc = zmq_connect (pushey, "inproc://crosstalk");
  assert (rc == 0);

  while (1) {
    char *string = s_recv (receiver);
    s_send (pushey, string);
  }

  zmq_close (pushey);
  zmq_close (receiver);
  pthread_exit (NULL);
}

int main (void)
{
  void *context = zmq_ctx_new ();
  int rc;
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);

  pthread_t publish_thread, receive_thread;
  rc = pthread_create (&publish_thread, &attr, &publish, context);
  assert (rc == 0);
  rc = pthread_create (&receive_thread, &attr, &receive, context);
  assert (rc == 0);

  void *status;
  rc = pthread_join (publish_thread, &status);
  assert(rc == 0);
  rc = pthread_join (receive_thread, &status);
  assert(rc == 0);

  pthread_attr_destroy (&attr);
  zmq_ctx_destroy (context);
  pthread_exit (NULL);
}
