#ifndef MAATOMIC_H
#define MAATOMIC_H

#include <type_traits>
#include "mamutex.h"

namespace manch1n  //manch1n's namespace
{
#define RETINT(TYPE) typename std::enable_if<std::is_arithmetic<TYPE>::value,TYPE>::type 
template <typename T>
class maatomic:uncopyable
{
public:
    maatomic();
    RETINT(T) load();           //return current 
    RETINT(T) store(T other);    //return old

    typename std::enable_if<std::is_arithmetic<T>::value,bool>::type ifZero();
    RETINT(T) operator++(int);     //return newval
    RETINT(T) operator--(int);      //return newval
private:
    T _num;
    mamutex _mamutex;
};

template <typename T>
maatomic<T>::maatomic():_num()
{}

template <typename T>
RETINT(T) maatomic<T>::load()
{
    mamutexLockGuard lock(_mamutex);
    return _num;
}

template <typename T>
RETINT(T) maatomic<T>::store(T newval)
{
    mamutexLockGuard lock(_mamutex);
    T oldval;
    oldval=_num;
    _num=newval;
    return oldval;
}

template <typename T>
RETINT(T) maatomic<T>::operator++(int)
{
    mamutexLockGuard lock(_mamutex);
    _num++;
    return _num;
}

template <typename T>
RETINT(T) maatomic<T>::operator--(int)
{
    mamutexLockGuard lock(_mamutex);
    _num--;
    return _num;
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value,bool>::type maatomic<T>::ifZero()
{
    mamutexLockGuard lock(_mamutex);
    return _num==0;
}



}

#endif //MAATOMIC_H
