#include "mathreadpool.h"

namespace manch1n
{
mathreadpool::mathreadpool(size_t nthreads) : _nthreads(nthreads),_run(false)
{
}

void mathreadpool::initAndRun()
{
    _run=true;
    for (int i = 0; i < _nthreads; ++i)
    {
        std::thread t(routine, this);
        t.detach();
        _threads.push_back(t.get_id());
    }
}

void *mathreadpool::routine(void *arg)
{
    mathreadpool &pool = *static_cast<mathreadpool *>(arg);
    while (pool._run)
    {
        matask ptask = pool.popTask();
        auto& [func,arg]=ptask;
        func(arg);
    }
    return NULL;
}

void mathreadpool::pushTask(matask &t)
{
    {
        lockGuard lock(_mutex);
        _matasks.push(t);
    }
    _condition.notify_one();
}

matask mathreadpool::popTask()
{
    uniqueLock lock(_mutex);
    _condition.wait(lock,[this](){return !this->isEmpty();});
    matask p(_matasks.front());
    _matasks.pop();
    return p;
}

bool mathreadpool::isEmpty()
{
    return _matasks.empty();
}

void mathreadpool::stop()
{
    _run=false;
}

} // namespace manch1n