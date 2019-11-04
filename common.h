#ifndef COMMON_H
#define COMMOM_H

namespace manch1n
{
class copyable
{

};

class uncopyable
{
public:
    uncopyable(){}
    ~uncopyable(){}
private:
    uncopyable(const uncopyable&);
    const uncopyable& operator=(const uncopyable&);
};


}

#endif