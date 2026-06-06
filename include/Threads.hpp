#pragma once
#include <unordered_map>
#include <vector>
#include <thread>
#include <functional>

#include "Tasks.hpp"
#include "Datatypes.hpp"
#include "Jobmap.hpp"
#include "Queue.hpp"




class Threads
{
private:
    Tasks m_Tasks;
    Threadqueue<IncomingData>& m_qIncoming;
    Threadqueue<StockData>& m_qOutcoming;
    Threadqueue<ComputingData> m_qComputing;
    JobMap m_mapJobMap;
    std::vector<std::thread> m_vtConsumerThreads;
    std::vector<std::thread> m_vtApiThreads;
    int m_iComputingThreads; 
    int m_iApiThreads;
private:
    void apiThreadfunction();
    void computationFunction();
public:
    Threads(Threadqueue<IncomingData>& qIncoming, Threadqueue<StockData>& qOutcoming, int iThreads, int iApiThreads);
    ~Threads();
 
    void startApiThreads();
    void startComputationThreads();

   
};


