#include "masharedptr.h"
#include <iostream>
#include <iomanip>
#include <thread>
using namespace manch1n;
using namespace std;
class base
{
public:
    virtual void print()
    {
        cout << "base.test failed.\n";
    }
};

class drive : public base
{
public:
    virtual void print() override
    {
        cout << "this is a virtual function drived class.test success!\n";
    }
};

int main(int argc, char **argv)
{
    cout << "test ptr accept a drived class raw pointer" << endl;
    mashared_ptr<base> ptr(new drive);

    cout<<"test in multi thread env."<<endl;
    mashared_ptr<int> intptr(new int(111));
    thread t1([&]() {
        for (int i = 0; i < 100; ++i)
        {
            auto tmpptr(intptr);
        }
    });
    t1.detach();
    thread t2([&]() {
        for (int i = 0; i < 100; ++i)
        {
            auto tmpptr(intptr);
        }
    });
    t2.detach();
    if(intptr.count()==1)
    {
        cout<<"multi thread test success!"<<endl;
    }
    else
    {
        cout<<"multithread test failed"<<endl;
    }
    
    return 0;
}