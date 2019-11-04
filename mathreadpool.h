#ifndef MATHREADPOOL_H
#define MATHREADPOOL_H
#include <queue>
#include "common.h"
#include <vector>
#include <condition_variable>
#include <mutex>
#include <future>
#include <memory>
#include <functional>

namespace manch1n
{
using matask=std::pair<std::function<void(void*)>,void*>;
class mathreadpool : uncopyable
{
public:
    using lockGuard = std::lock_guard<std::mutex>;
    using uniqueLock = std::unique_lock<std::mutex>;

    explicit mathreadpool(size_t nthreads = 4);
    void initAndRun();
    void pushTask(matask &);
    bool isEmpty();
    void stop();
private:
    static void *routine(void *arg);
    bool _run;
    matask popTask();
    std::vector<std::thread::id> _threads;
    std::queue<matask> _matasks;
    size_t _nthreads;
    std::mutex _mutex;
    std::condition_variable _condition;
};

} // namespace manch1n

#endif //MATHREADPOOL_H