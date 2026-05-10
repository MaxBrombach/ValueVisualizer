#include "Threads.hpp"

void Threads::threadFunction()
{
    //TODO
}

Threads::Threads(int iThreads) : m_iThreadCount(iThreads)
{

}

Threads::~Threads()
{   
    for (auto& thrd : m_vtConsumerThreads) 
    {
        if (thrd.joinable()) 
        {
            thrd.join();
        }
    }
}

void Threads::startThreads()
{
    for(int i = 0; i < m_iThreadCount; ++i)
    {
        m_vtConsumerThreads.emplace_back([this](){threadFunction();});
    }
        
}
