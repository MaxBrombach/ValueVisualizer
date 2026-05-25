#include "Threads.hpp"




Threads::Threads(Threadqueue<IncomingData>& qIncoming, Threadqueue<StockData>& qOutcoming, int iComputationThreads, int iApiThreads) : m_qIncoming(qIncoming), m_qOutcoming(qOutcoming), m_iComputingThreads(iComputationThreads), m_iApiThreads(iApiThreads)
{

}

Threads::~Threads()
{   
  
    for (auto& thrd : m_vtConsumerThreads) 
    {
        if (thrd.joinable())         
            thrd.join();    
    }
    for (auto& thrd : m_vtApiThreads) 
    {
        if (thrd.joinable())         
            thrd.join();    
    }
}



void Threads::startApiThreads()
{
    for(int i = 0; i < m_iApiThreads; ++i)
    {
        m_vtConsumerThreads.emplace_back([this](){apiThreadfunction();});
    }        
}

void Threads::startComputationThreads()
{
    for(int i = 0; i < m_iComputingThreads; ++i)
    {
        m_vtConsumerThreads.emplace_back([this](){computingfunction();});
    }
}

void Threads::apiThreadfunction()
{
    while(true)
    {
        IncomingData sIncomingData = m_qIncoming.pop();
        auto jsonresponse = m_Tasks.fetchStock(sIncomingData);
        auto result = jsonresponse["chart"]["result"][0];
        auto timestamps = result["timestamp"];
        auto closes = result["indicators"]["quote"][0]["close"];

        ComputingData sComputingData;
        sComputingData.strStockticker = result["meta"]["symbol"];
        for (int i = 0; i < timestamps.size(); ++i)
        {
            sComputingData.fStockprice = closes[i];
            sComputingData.lTimestamp = timestamps[i];  
        }
        m_qComputing.push(sComputingData);       
    }
    
}

void Threads::computingfunction()
{
    while (true)
    {
        ComputingData sComputingData= m_qComputing.pop();
        // TODO 
    }
}
