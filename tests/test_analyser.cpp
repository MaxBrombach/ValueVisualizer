#include <gtest/gtest.h>
#include "Tasks.hpp"

TEST(TrendlineTest, DetectsUpperTrendlineHighs)
{
    Tasks tasks;

    ComputingData data;
    data.strStockticker = "TEST";
    data.vlTimestamps = {1,2,3,4,5,6,7,8,9};
    data.vfStockprice = {10, 12, 15, 13, 14, 13, 18, 16, 14};


    StockData result = tasks.computeUpperTrendline(data);

    //ASSERT_EQ(result.vTrendlines.size(), 1);

    

    Trendline trendline = result.vTrendlines[0];
    StockPrice fStockpricep1 = trendline.pPoint1.second;
    StockPrice fStockpricep2 = trendline.pPoint2.second;
    EXPECT_EQ(fStockpricep1, 15);
    EXPECT_EQ(fStockpricep2, 18);
}
