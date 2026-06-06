#include <unordered_map>
#include <string>
#include <shared_mutex>
#include "Datatypes.hpp"


class JobMap
{
private:
    std::unordered_map<std::string, std::vector<Trendline>> mapTrendline;
    std::shared_mutex counterMutex;
public:
    

    std::vector<Trendline> getTrendline(const std::string& ticker) 
    {
        std::shared_lock<std::shared_mutex> lock(counterMutex);
        
        auto it = mapTrendline.find(ticker);
        return it->second;
        
    }
    void clearEntry(const std::string& ticker) 
    {
        std::unique_lock<std::shared_mutex> lock(counterMutex);
        mapTrendline.erase(ticker);
    }

    void insertTrendline(const std::string& ticker, std::vector<Trendline> vTrendline)
    {
        std::unique_lock<std::shared_mutex> lock(counterMutex);
        mapTrendline[ticker] = vTrendline;
    }

    bool contains(const std::string& ticker)
    {
        std::unique_lock<std::shared_mutex> lock(counterMutex);
        return mapTrendline.contains(ticker);
    }


};




