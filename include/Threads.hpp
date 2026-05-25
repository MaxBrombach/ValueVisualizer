#pragma once
#include <unordered_map>
#include <vector>
#include <thread>

#include "Tasks.hpp"
#include "Datatypes.hpp"
#include "Queue.hpp"




class Threads
{
private:
    Tasks m_Tasks;
    Threadqueue<IncomingData>& m_qIncoming;
    Threadqueue<StockData>& m_qOutcoming;
    Threadqueue<ComputingData> m_qComputing;
    std::vector<std::thread> m_vtConsumerThreads;
    std::vector<std::thread> m_vtApiThreads;
    int m_iComputingThreads; 
    int m_iApiThreads;
private:
    void threadFunction();
public:
    Threads(Threadqueue<IncomingData>& qIncoming, Threadqueue<StockData>& qOutcoming, int iThreads, int iApiThreads);
    ~Threads();
 
    void startApiThreads();
    void startComputationThreads();

    void apiThreadfunction();
    void computingfunction();
};


