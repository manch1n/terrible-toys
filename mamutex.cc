#include "mamutex.h"

namespace manch1n
{
mamutex::mamutex()
{
    ::pthread_mutex_init(&_mutex,NULL);
}

int mamutex::lock()
{
    return ::pthread_mutex_lock(&_mutex);
}

int mamutex::unlock()
{
    return ::pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t* mamutex::getmutex()
{
    return &_mutex;
}

mamutexLockGuard::mamutexLockGuard(mamutex& mutex):_mutex(mutex)
{
    _mutex.lock();
}



}