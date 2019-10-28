#ifndef MAMUTEX_H
#define MAMUTEX_H

#include <pthread.h> //mutex
#include "common.h"  //uncopy

namespace manch1n
{
class mamutexLockGuard;
class mamutex : public uncopyable //RAII class
{
public:
    friend mamutexLockGuard;

    mamutex();
    pthread_mutex_t *getmutex(); //effective c++ clause15
    ~mamutex()
    {
        ::pthread_mutex_destroy(&_mutex);
    }

private:
    int lock();
    int unlock();

private:
    pthread_mutex_t _mutex;
};

class mamutexLockGuard : public uncopyable
{
public:
    mamutexLockGuard(mamutex &mutex);
    ~mamutexLockGuard()
    {
        _mutex.unlock();
    }
    mamutex &_mutex;
};

} // namespace manch1n

#endif //MAMUTEX_H