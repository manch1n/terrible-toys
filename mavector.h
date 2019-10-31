#ifndef MAVECTOR_H
#define MAVECTOR_H
#include <stdlib.h> //malloc
#include <string.h> //memcpy
#include <utility>  //std::move
#include <vector>
namespace manch1n
{

template <typename T>
class mavector
{
public:
    using size_type = size_t;
    using iterater = T *;
    using const_iterater = const T *;

public:
    explicit mavector(size_type s = 50);
    explicit mavector(const mavector<T> &);
    explicit mavector(mavector<T> &&);
    mavector &operator=(const mavector<T> &other);
    mavector &operator=(mavector<T> &&other);
    ~mavector();

public:
    const T &operator[](size_type) const;
    T &operator[](size_type);
    void push_back(const T &element);
    void resize(size_type news);
    size_type size() const;
    size_type capacity() const;
    iterater begin();
    iterater end();
    void swap(mavector<T> &left, mavector<T> &right);

private:
    size_type _capacity;
    size_type _size;
    T *_underlying;
    static const size_type _factor = 2;
};

template <typename T>
mavector<T>::mavector(mavector::size_type s) : _size(0), _capacity(s)
{
    _underlying = new T[s]; //default constructer
}

template <typename T>
mavector<T>::~mavector()
{
    delete[] _underlying;
}

template <typename T>
void mavector<T>::push_back(const T &element)
{
    if (_size == _capacity)
    {
        resize(_capacity * _factor);
    }
    _underlying[_size] = element; //copy
    _size++;
}

template <typename T>
void mavector<T>::resize(mavector::size_type newsize)
{
    if (newsize <= _capacity)
    {
        return;
    }
    T *newunderlying = ::malloc(sizeof(T) * _capacity);
    //use move?
    // for(size_type i=0;s<_capacity;++i)
    // {
    //     newunderlying[s]=std::move(_underlying[s]);
    // }
    ::memcpy(newunderlying, _underlying, sizeof(T) * _capacity);
    delete[] _underlying;
    _underlying = newunderlying;
    _capacity = newsize;
}

template <typename T>
mavector<T>::size_type mavector<T>::size() const
{
    return _size;
}

template <typename T>
mavector<T>::size_type mavector<T>::capacity() const
{
    return _capacity;
}

template <typename T>
mavector<T>::iterater mavector<T>::begin()
{
    return _underlying;
}

template <typename T>
mavector<T>::iterater mavector<T>::end()
{
    return _underlying + _capacity;
}

template <typename T>
mavector<T>::mavector(const mavector<T> &other) : _capacity(other._capacity), _size(other._size)
{
    _underlying = ::malloc(sizeof(T) * _capacity);
    ::memcpy(_underlying, other._underlying, sizeof(T) * _capacity);
}

template <typename T>
mavector<T> &mavector<T>::operator=(const mavector<T> &other) //copy and swap
{
    mavector<T> tmp(other);
    using std::swap;
    swap(tmp, *this);
    return *this;
}

template <typename T>
mavector<T>::mavector(mavector<T> &&other) : _capacity(other._capacity), _size(other._size), _underlying(other._underlying)
{
    other._underlying = nullptr;
}

template <typename T>
mavector<T> &mavector<T>::operator=(mavector<T> &&other)
{
    delete[] _underlying;
    _size = other._size;
    _capacity = other._capacity;
    _underlying = other._underlying;
    other._underlying = nullptr;
}

template <typename T>
const T &mavector<T>::operator[](mavector<T>::size_type loc) const
{
    if (loc >= _size)
    {
        throw std::exception();
    }
    return _underlying[loc];
}

template <typename T>
T &mavector<T>::operator[](mavector<T>::size_type loc)
{
    return const_cast<T &>(static_cast<const mavector<T> &>(*this)[loc]);
}

template <typename T>
void mavector<T>::swap(mavector<T> &left, mavector<T> &right)
{
    using std::swap;
    swap(left._size, right._size);
    swap(left._capacity, right._underlying);
    swap(left._underlying, right._underlying);
}

} // namespace manch1n
#endif //MAVECTOR_H