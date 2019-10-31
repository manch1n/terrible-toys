#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "mathreadpool.h"
using namespace std;
using namespace manch1n;

class drive1:public manch1n::task
{
public:
    virtual void execute() override
    {
        cout<<s<<endl;
    }
    string s="drive1";
};

class drive2:public manch1n::task
{
public:
    virtual void execute() override
    {
        cout<<s<<endl;
    }
    string s="drive2";
};

int main(int argc, char **argv)
{
    taskSPtr d1=make_shared<drive1>();
    taskSPtr d2=make_shared<drive2>();
    mathreadpool pool(4);
    pool.initAndRun();
    pool.pushTask(d1);
    pool.pushTask(d2);
    ::pause();
    return 0;
}