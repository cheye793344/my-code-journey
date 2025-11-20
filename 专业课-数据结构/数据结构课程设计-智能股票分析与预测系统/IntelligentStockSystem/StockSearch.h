#pragma once
#include "Stock.h"
#include <vector>
#include <string>

namespace StockFunctions {
    // 第4关：基于折半查找的股票信息查找
    void binarySearchStock();

    // 第5关：基于二叉排序树的股票信息查找  
    void BSTSearchStock();

    // 第6关：基于字典树的股票信息查找
    void trieSearchStock();

    // 第7关：基于开放地址法的股票信息查找
    void openHashSearchStock();

    // 第8关：基于链地址法的股票信息查找
    void chainHashSearchStock();
}