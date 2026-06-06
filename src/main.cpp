#include <httplib.h>
#include <json.hpp>
#include "Threads.hpp"
#include "Datatypes.hpp"
#include "Queue.hpp"


// --- serialize Stockpricetuple (std::pair<Timestamp, StockPrice>) ---
inline void to_json(nlohmann::json& j, const Stockpricetuple& p)
{
    j = nlohmann::json{
        {"timestamp", p.first},
        {"price",     p.second}
    };
}

// --- serialize Trendline ---
inline void to_json(nlohmann::json& j, const Trendline& t)
{
    j = nlohmann::json{
        {"slope",     t.fSlope},
        {"intercept", t.fIntercept},
        {"point1",    t.pPoint1},
        {"point2",    t.pPoint2}
    };
}

// --- serialize StockData ---
inline void to_json(nlohmann::json& j, const StockData& s)
{
    j = nlohmann::json{
        {"ticker",      s.strStockticker},
        {"prices",      s.vStockvalue},
        {"timestamps",  s.vTimeStamp},
        {"trendlines",  s.vTrendlines}
    };
}



int main(int argc, char const *argv[])
{
    Threadqueue<IncomingData> qIncoming;
    Threadqueue<StockData> qOutcoming;    

    Threads threadPool(qIncoming, qOutcoming, 10, 1);
    threadPool.startApiThreads();
    threadPool.startComputationThreads();
    

    httplib::Server server;

    server.Post("/request", [&](const httplib::Request& req, httplib::Response& res) 
    {
        auto json = nlohmann::json::parse(req.body);    
        IncomingData sIncomingData;
        sIncomingData.strStockticker = json["Ticker"];
        sIncomingData.strGranularity  = json["Granularity"];
        sIncomingData.strRange = json["Range"]; 
        sIncomingData.iWindowsize = json["Windowsize"];
        qIncoming.push(sIncomingData);  
        res.set_content("OK", "text/plain");
    });

    server.Get("/result", [&](const httplib::Request& req, httplib::Response& res) 
    {
        StockData stockData;
        stockData = qOutcoming.pop();   // wait for worker thread to produce result

        nlohmann::json j = stockData;
        res.set_content(j.dump(), "application/json");
    });


    server.listen("0.0.0.0", 8080);
}
