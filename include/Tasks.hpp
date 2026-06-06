#include <curl/curl.h>
#include <string>
#include <cstddef>
#include <json.hpp>
#include "Datatypes.hpp"
#include "Queue.hpp"




class Tasks
{
private:

private:
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
public:
StockData computeUpperTrendline(const ComputingData& sComputingData);
StockData computeLowerTrendline(const ComputingData& sComputingData);
bool isHigh(StockPrice fHigh, const std::vector<StockPrice>& vfStockPrices, int iWindowsize, int iIndex);
bool isLow(StockPrice fLow, const std::vector<StockPrice>& vfStockPrices, int iWindowsize, int iIndex);
std::vector<Trendline> computeTrendlines(const std::vector<Stockpricetuple>& vStockpricepoints);
nlohmann::json fetchStock(IncomingData sIncomingData);


};