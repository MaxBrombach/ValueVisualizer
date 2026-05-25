#include "Queue.hpp"



template<typename T> 
void Threadqueue<T>::push(const T& queueElement)
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        m_qTaskqueue.push(queueElement);
    }
    condvar.notify_one();
    
}

template<typename T>
T Threadqueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(mutex);
    condvar.wait(lock, [&]{ return !m_qTaskqueue.empty(); });

        T value = m_qTaskqueue.front();
        m_qTaskqueue.pop();
        return value;
}
 
template<typename T>
bool Threadqueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_qTaskqueue.empty();
}