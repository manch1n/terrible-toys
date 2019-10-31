#include "mathreadpool.h"

namespace manch1n
{
mathreadpool::mathreadpool(size_t nthreads) : _nthreads(nthreads)
{
}

void mathreadpool::initAndRun()
{
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
    while (1)
    {
        taskSPtr ptask = pool.popTask();
        ptask->execute();
    }
    return NULL;
}

void mathreadpool::pushTask(taskSPtr &t)
{
    {
        lockGuard lock(_mutex);
        _tasks.push(t);
    }
    _condition.notify_one();
}

taskSPtr mathreadpool::popTask()
{
    uniqueLock lock(_mutex);
    _condition.wait(lock,[this](){return !this->isEmpty();});
    taskSPtr p(_tasks.front());
    _tasks.pop();
    return p;
}

bool mathreadpool::isEmpty()
{
    return _tasks.empty();
}

} // namespace manch1n