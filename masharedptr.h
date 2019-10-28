#ifndef MASHAREDPTR_H
#define MASHAREDPTR_H

#include "maatomic.h"
#include <utility> //std::swap
namespace manch1n
{

template <typename T>
class mashared_ptr : public copyable //for simplicity,assume that ptr has not const and not support array deconstruct
{
public:
    mashared_ptr(T *ptr);
    mashared_ptr(mashared_ptr<T> &other);
    mashared_ptr();

    template <class Y>
    explicit mashared_ptr(Y *ptr);
    template <class Y>
    explicit mashared_ptr(mashared_ptr<Y> &other);

    mashared_ptr<T> &operator=(mashared_ptr &other);
    template <class Y>
    mashared_ptr<T> &operator=(mashared_ptr<Y> &other);

    mashared_ptr<T>(mashared_ptr<T>&& other);
    mashared_ptr<T>& operator=(mashared_ptr<T>&& other);

    T *get() const;
    void reset();
    int count() const;

    T &operator*() const
    {
        return *_ptr;
    }
    T *operator->() const
    {
        return &this->operator*();
    }
    ~mashared_ptr()
    {
        (*_reference)--;
        test();
    }

private:
    void test(); //test the refernce .if zero then deconstruct.
    ma_atomic<int> *_reference;
    T *_ptr;
};

template <typename T>
mashared_ptr<T>::mashared_ptr(T *ptr) : _ptr(ptr)
{
    _reference = new ma_atomic<int>;
    _reference->store(1);
}

template <typename T>
mashared_ptr<T>::mashared_ptr(mashared_ptr<T> &other) : _ptr(other._ptr), _reference(other._reference)
{ //maybe before this line,other has been deconstructed.
    (*_reference)++;
}

template <typename T>
template <class Y>
mashared_ptr<T>::mashared_ptr(Y *ptr)
{
    _reference = new ma_atomic<int>;
    _reference->store(1);
    _ptr = ptr; //this assignment should be explict supported.
}

template <typename T>
template <class Y>
mashared_ptr<T>::mashared_ptr(mashared_ptr<Y> &ptr) : _reference(ptr._reference)
{
    (*_reference)++;
    _ptr = ptr; //this assignment should be explicit supported.
}

template <typename T>
mashared_ptr<T>::mashared_ptr() : _reference(nullptr), _ptr(nullptr)
{
}

template <typename T>
mashared_ptr<T> &mashared_ptr<T>::operator=(mashared_ptr<T> &other) //copy and swap
{
    mashared_ptr<T> tmp(other);
    using std::swap;
    swap(tmp, *this); //to do
    return *this;
}

template <typename T>
template <class Y>
mashared_ptr<T> &mashared_ptr<T>::operator=(mashared_ptr<Y> &other)
{
    _reference = other._reference;
    _ptr = other._ptr; //pointer assignment should be explicit supported.
    (*_reference)++;
}

template <typename T>
T *mashared_ptr<T>::get() const
{
    return _ptr;
}

template <typename T>
void mashared_ptr<T>::test()
{
    if (_reference->ifZero()) //intential risk
    {
        delete _ptr;
        delete _reference;
        _ptr=nullptr;
        _reference=nullptr;
    }
}

template <typename T>
void mashared_ptr<T>::reset()
{
    (*_reference)--;
    test();
}

template <typename T>
mashared_ptr<T>::mashared_ptr(mashared_ptr<T>&& other)
{
    _reference=other._reference;
    _ptr=other._ptr;
    (*_reference)++;    //othre will then call deconstructer
}

template <typename T>
mashared_ptr<T>& mashared_ptr<T>::operator=(mashared_ptr<T>&& other)
{
    _reference=other._reference;
    _ptr=other._ptr;
    (*_reference)++;
}

template <typename T>
int mashared_ptr<T>::count()const
{
    return _reference->load();
}

} // namespace manch1n

#endif //MASHAREDPTR_H