#include <gtest/gtest.h>
#include "Tasks.hpp"

TEST(TrendlineTest, DetectsUpperTrendlineHighs)
{
    Tasks tasks;

    ComputingData data;
    data.strStockticker = "TEST";
    data.vlTimestamps = {1,2,3,4,5,6,7,8,9};
    data.vfStockprice = {10, 12, 15, 13, 14, 13, 18, 16};

    StockData result = tasks.computeUpperTrendline(data);

    //ASSERT_EQ(result.vTrendlines.size(), 1);

    const auto& tl = result.vTrendlines[0];

   
    //EXPECT_EQ(, 15);
    //EXPECT_EQ(tl.p2.second, 18);
}
