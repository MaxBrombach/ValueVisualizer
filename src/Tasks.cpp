#include "Tasks.hpp"


// Callback to store the HTTP response in a std::string
size_t Tasks::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

StockData Tasks::computeUpperTrendline(const ComputingData &sComputingData)
{
    bool bRideDown = false;
    std::vector<Stockpricetuple> vUpperTrendlineHighs;

    StockPrice fHigh = sComputingData.vfStockprice[0];
    for (int i = 0; i < sComputingData.vlTimestamps.size(); ++i)
    {            
        StockPrice fSPrice = sComputingData.vfStockprice[i];
        if (!bRideDown)
        {
            if (fSPrice > fHigh)                   
                fHigh = fSPrice;         
            else 
            {
                if(isHigh(fHigh, sComputingData.vfStockprice, sComputingData.iWindowsize, i))
                {
                    vUpperTrendlineHighs.push_back({sComputingData.vlTimestamps.at(i), fHigh});
                    fHigh = sComputingData.vfStockprice[i];  
                    bRideDown = true;                                 
                }                
            }
        }
        else
        {
            if (fSPrice > fHigh) 
            {
                bRideDown = false;
                fHigh = fSPrice;
            }                
        }        
    }

    std::vector<Trendline> vTrendlines = computeTrendlines(vUpperTrendlineHighs);
    StockData stockData;
    stockData.strStockticker = std::move(sComputingData.strStockticker);
    stockData.vTimeStamp     = std::move(sComputingData.vlTimestamps);
    stockData.vStockvalue    = std::move(sComputingData.vfStockprice);
    stockData.vTrendlines    = std::move(vTrendlines);
    return stockData;
}

StockData Tasks::computeLowerTrendline(const ComputingData &sComputingData)
{
    
    bool bRideUp = false;
    std::vector<Stockpricetuple> vLowerTrendlineLows;

    StockPrice fLow = sComputingData.vfStockprice[0];
    for (int i = 0; i < sComputingData.vlTimestamps.size(); ++i)
    {            
        StockPrice fSPrice = sComputingData.vfStockprice[i];
        if (!bRideUp)
        {
            if (fSPrice < fLow)                   
                fLow = fSPrice;         
            else 
            {
                if(isLow(fLow, sComputingData.vfStockprice, sComputingData.iWindowsize, i))
                {
                    vLowerTrendlineLows.push_back({sComputingData.vlTimestamps.at(i), fLow});
                    fLow = sComputingData.vfStockprice[i];  
                    bRideUp = true;                                 
                }                
            }
        }
        else
        {
            if (fSPrice < fLow) 
            {
                bRideUp = false;
                fLow = fSPrice;
            }                 
        }        
    }

    std::vector<Trendline> vTrendlines = computeTrendlines(vLowerTrendlineLows);
    StockData stockData;
    stockData.strStockticker = std::move(sComputingData.strStockticker);
    stockData.vTimeStamp     = std::move(sComputingData.vlTimestamps);
    stockData.vStockvalue    = std::move(sComputingData.vfStockprice);
    stockData.vTrendlines    = std::move(vTrendlines);
    return stockData;
}

bool Tasks::isHigh(StockPrice fHigh, const std::vector<StockPrice>& vfStockPrices, int iWindowsize, int iIndex)
{
    bool bHigh = true;  
    StockPrice fStockprice = 0;
    for(int i = iIndex; i < iIndex + iWindowsize - 1; ++i)
    {     
        fStockprice = vfStockPrices[i + 1];   
        if(fHigh <= fStockprice)
        {
            bHigh = false;
            break;            
        }                     
    }      
    return bHigh;       
}

bool Tasks::isLow(StockPrice fLow, const std::vector<StockPrice>& vfStockPrices, int iWindowsize, int iIndex)
{
    bool bLow = true;  
    StockPrice fStockprice = 0;
    for(int i = iIndex; i < iIndex + iWindowsize - 1; ++i)
    {     
        fStockprice = vfStockPrices[i + 1];   
        if(fLow >= fStockprice)
        {
            bLow = false;
            break;            
        }                     
    }      
    return bLow; 
}

std::vector<Trendline> Tasks::computeTrendlines(const std::vector<Stockpricetuple> &vStockpricepoints)
{
    std::vector<Trendline> vTrendlines; 
    Trendline trendline; 
    for(int i = 0; i < vStockpricepoints.size() - 1; ++i)
    {
        auto& [lTsCurrent, fPriceCurrent] = vStockpricepoints[i];
        auto& [lTsNext, fPriceNext] = vStockpricepoints[i+1];

        float fSlope     = (fPriceNext - fPriceCurrent) / float(lTsNext - lTsCurrent);
        float fIntercept = fPriceCurrent - fSlope * lTsCurrent;

        trendline.fSlope     = (fPriceNext - fPriceCurrent) / float(lTsNext - lTsCurrent);
        trendline.fIntercept = fPriceCurrent - fSlope * lTsCurrent;
        trendline.pPoint1 = {lTsCurrent, fPriceCurrent};
        trendline.pPoint2 = {lTsNext, fPriceNext};
        vTrendlines.push_back(trendline);
    }
    return vTrendlines;
}

nlohmann::json Tasks::fetchStock(IncomingData sIncomingData)
{    
    std::string url = "https://query1.finance.yahoo.com/v8/finance/chart/"  + sIncomingData.strStockticker + "?interval=" + sIncomingData.strGranularity + "&range="+ sIncomingData.strRange;
    nlohmann::json jsonresponse;
    CURL* curl = curl_easy_init();
    std::string response;

    curl_easy_setopt(curl, CURLOPT_USERAGENT,
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
    "AppleWebKit/537.36 (KHTML, like Gecko) "
    "Chrome/124.0.0.0 Safari/537.36");

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res= curl_easy_perform(curl);

        if (res != CURLE_OK) {
           // std::cerr << "curl error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        jsonresponse = nlohmann::json::parse(response);
    
    }
    return jsonresponse;

}

