#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 第7关：开放地址法哈希表
class OpenAddressingHashTable {
private:
    static const int TABLE_SIZE = 400;
    vector<Stock*> table;
    int elementCount;
    int totalComparisons;

    int hash(const string& key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += (i * i * int(key[i]));
        }
        return sum % 397;
    }

public:
    OpenAddressingHashTable() : table(TABLE_SIZE, nullptr), elementCount(0), totalComparisons(0) {}

    void insert(Stock* stock) {
        int index = hash(stock->englishName);
        int comparisons = 1;

        while (table[index] != nullptr) {
            comparisons++;
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = stock;
        elementCount++;
        totalComparisons += comparisons;
    }

    Stock* search(const string& key) {
        int index = hash(key);
        int startIndex = index;

        while (table[index] != nullptr) {
            if (table[index]->englishName == key) {
                return table[index];
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }

        return nullptr;
    }

    double getASL() const {
        if (elementCount == 0) return 0.0;
        return static_cast<double>(totalComparisons) / elementCount;
    }
};

// 第8关：链地址法哈希表
struct HashNode {
    Stock* stock;
    HashNode* next;

    HashNode(Stock* s) : stock(s), next(nullptr) {}
};

class ChainingHashTable {
private:
    static const int TABLE_SIZE = 400;
    vector<HashNode*> table;
    int elementCount;
    int totalComparisons;

    int hash(const string& key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += (i * i * int(key[i]));
        }
        return sum % 397;
    }

public:
    ChainingHashTable() : table(TABLE_SIZE, nullptr), elementCount(0), totalComparisons(0) {}

    void insert(Stock* stock) {
        int index = hash(stock->englishName);
        HashNode* newNode = new HashNode(stock);

        if (table[index] == nullptr) {
            table[index] = newNode;
            totalComparisons += 1;
        }
        else {
            HashNode* current = table[index];
            int comparisons = 1;
            while (current->next != nullptr) {
                comparisons++;
                current = current->next;
            }
            current->next = newNode;
            totalComparisons += comparisons + 1;
        }

        elementCount++;
    }

    Stock* search(const string& key) {
        int index = hash(key);
        HashNode* current = table[index];
        int comparisons = 0;

        while (current != nullptr) {
            comparisons++;
            if (current->stock->englishName == key) {
                return current->stock;
            }
            current = current->next;
        }

        return nullptr;
    }

    double getASL() const {
        if (elementCount == 0) return 0.0;
        return static_cast<double>(totalComparisons) / elementCount;
    }
};

void StockFunctions::openHashSearchStock() {
    MenuSystem menu;
    system("cls");
    cout << "==========================================" << endl;
    cout << "   基于开放地址法的股票信息查找" << endl;
    cout << "==========================================" << endl;

    // 读取股票数据
    cout << "正在读取股票数据..." << endl;
    vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

    if (allStocks.empty()) {
        menu.showMessage("错误：无法读取股票数据文件或文件为空！");
        return;
    }

    // 构建哈希表
    OpenAddressingHashTable hashTable;
    for (auto& stock : allStocks) {
        hashTable.insert(&stock);
    }

    cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

    // 输入要查找的股票英文名
    string sname = menu.getInput("请输入要查找的股票英文名称: ");

    Stock* foundStock = hashTable.search(sname);

    if (foundStock != nullptr) {
        cout << "查找成功！" << endl;
        foundStock->displayInfo();

        double ASL = hashTable.getASL();
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    menu.showMessage(""); // 等待按键
}

void StockFunctions::chainHashSearchStock() {
    MenuSystem menu;
    system("cls");
    cout << "==========================================" << endl;
    cout << "   基于链地址法的股票信息查找" << endl;
    cout << "==========================================" << endl;

    // 读取股票数据
    cout << "正在读取股票数据..." << endl;
    vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

    if (allStocks.empty()) {
        menu.showMessage("错误：无法读取股票数据文件或文件为空！");
        return;
    }

    // 构建哈希表
    ChainingHashTable hashTable;
    for (auto& stock : allStocks) {
        hashTable.insert(&stock);
    }

    cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

    // 输入要查找的股票英文名
    string sname = menu.getInput("请输入要查找的股票英文名称: ");

    Stock* foundStock = hashTable.search(sname);

    if (foundStock != nullptr) {
        cout << "查找成功！" << endl;
        foundStock->displayInfo();

        double ASL = hashTable.getASL();
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    menu.showMessage(""); // 等待按键
}