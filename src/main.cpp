#include <httplib.h>
#include <json.hpp>
#include "Threads.hpp"
#include "Datatypes.hpp"
#include "Queue.hpp"


int main(int argc, char const *argv[])
{
    Threadqueue<IncomingData> qIncoming;
    Threadqueue<StockData> qOutcoming;

    

    Threads threadPool(qIncoming, qOutcoming, 10, 5);


    httplib::Server server;

    server.Post("/request", [&](const httplib::Request& req, httplib::Response& res) {
        auto json = nlohmann::json::parse(req.body);    
        IncomingData sIncomingData;
        sIncomingData.strStockticker = json["Ticker"];
        sIncomingData.strGranularity  = json["Granularity"];
        sIncomingData.strRange = json["Range"]; 
        qIncoming.push(sIncomingData);  
        res.set_content("OK", "text/plain");
    });

    server.listen("0.0.0.0", 8080);
}
