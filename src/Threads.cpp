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
        m_vtConsumerThreads.emplace_back([this](){computationFunction();});
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
       
        sComputingData.vfStockprice = closes.get<std::vector<float>>();
        sComputingData.vlTimestamps = timestamps.get<std::vector<long>>();  
        
        sComputingData.eCompTask = ComputingTask::UpperTrendline;
        sComputingData.iWindowsize = sIncomingData.iWindowsize;
        m_qComputing.push(sComputingData);  
        sComputingData.eCompTask = ComputingTask::LowerTrendline;
        m_qComputing.push(sComputingData);  
       
    }
    
}

void Threads::computationFunction()
{
    while (true)
    {
        ComputingData compData = m_qComputing.pop();
        StockData stockData;
        if (compData.eCompTask == ComputingTask::UpperTrendline)
            stockData= m_Tasks.computeUpperTrendline(compData);
        else if (compData.eCompTask == ComputingTask::LowerTrendline)
            stockData = m_Tasks.computeLowerTrendline(compData);
        
        if (m_mapJobMap.contains(stockData.strStockticker))
        {
            std::vector<Trendline> storedTrendline = m_mapJobMap.getTrendline(stockData.strStockticker);
            stockData.vTrendlines.insert(stockData.vTrendlines.end(), storedTrendline.begin(), storedTrendline.end());
            m_mapJobMap.clearEntry(stockData.strStockticker);
            m_qOutcoming.push(stockData);            
        }
        else
        {
            m_mapJobMap.insertTrendline(stockData.strStockticker, stockData.vTrendlines);
        }
            
    }
}
