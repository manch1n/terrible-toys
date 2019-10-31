#ifndef MATHREADPOOL_H
#define MATHREADPOOL_H
#include <queue>
#include "common.h"
#include <vector>
#include <condition_variable>
#include <mutex>
#include <future>
#include <memory>

namespace manch1n
{
using taskSPtr = std::shared_ptr<manch1n::task>;
class mathreadpool : uncopyable
{
public:
    using lockGuard = std::lock_guard<std::mutex>;
    using uniqueLock = std::unique_lock<std::mutex>;

    explicit mathreadpool(size_t nthreads = 4);
    void initAndRun();
    void pushTask(taskSPtr &);
    bool isEmpty();

private:
    static void *routine(void *arg);

    taskSPtr popTask();
    std::vector<std::thread::id> _threads;
    std::queue<taskSPtr> _tasks;
    size_t _nthreads;
    std::mutex _mutex;
    std::condition_variable _condition;
};

} // namespace manch1n

#endif //MATHREADPOOL_H