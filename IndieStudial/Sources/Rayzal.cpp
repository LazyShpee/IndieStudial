#include "Rayzal.cpp"

rayzal::ListenerThread::ListenerThread(void)
  : _set(true)
{
}

rayzal::ListenerThread::~ListenerThread(void)
{
  if (this->_set)
    pthread_join(this->_thread_id, NULL);
}

bool rayzal::ListenerThread::start(void)
{
  this->_set = !pthread_create(&this->_thread_id, NULL, &this->loop, NULL);
  return (this->_set);
}

void *rayzal::ListenerThread::loop(void *args)
{
}
