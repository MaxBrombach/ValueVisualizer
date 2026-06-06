#pragma once

using StockPrice = float;
using Timestamp = long;
using Stockpricetuple = std::pair<Timestamp, StockPrice>;

enum class ComputingTask
{
    UpperTrendline,
    LowerTrendline
};

struct Trendline {
    float fSlope;
    float fIntercept;
    Stockpricetuple pPoint1;
    Stockpricetuple pPoint2;
};


struct StockData
{
    std::string strStockticker;
    std::vector<StockPrice> vStockvalue;
    std::vector<Timestamp> vTimeStamp;
    std::vector<Trendline> vTrendlines;
};



struct ComputingData
{
    std::string strStockticker;
    std::vector<Timestamp> vlTimestamps;
    std::vector<StockPrice> vfStockprice;
    int iWindowsize;
    ComputingTask eCompTask;

};

struct IncomingData
{
    std::string strGranularity;
    std::string strRange;
    std::string strStockticker;
    int iWindowsize;
};