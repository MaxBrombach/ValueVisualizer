#pragma once

using StockPrice = float;

struct StockData
{
    std::string strStockticker;
    std::unordered_map<long, StockPrice> umapStockvalue;
    std::vector<std::vector<std::pair<long, StockPrice>>> vvpffTrendlines;
};

struct ComputingData
{
    std::string strStockticker;
    long lTimestamp;
    StockPrice fStockprice;
};

struct IncomingData
{
    std::string strGranularity;
    std::string strRange;
    std::string strStockticker;
};