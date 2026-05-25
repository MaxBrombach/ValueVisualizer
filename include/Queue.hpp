#pragma once
#include <condition_variable>
#include <queue>
#include <utility>

template<typename T> 
class Threadqueue
{
private:
    std::queue<T> m_qTaskqueue;
    mutable std::mutex mutex;
    std::condition_variable condvar;
public:
    void push(const T& queueElement);
    T pop();
    bool empty() const;
};

#include "Queue.tpp"