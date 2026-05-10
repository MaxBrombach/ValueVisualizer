#pragma once

#include <vector>
#include <thread>

class Threads
{
private:
    std::vector<std::thread> m_vtConsumerThreads;
    int m_iThreadCount;
private:
    void threadFunction();
public:
    Threads(int iThreads = 10);
    ~Threads();

    void startThreads();
};

