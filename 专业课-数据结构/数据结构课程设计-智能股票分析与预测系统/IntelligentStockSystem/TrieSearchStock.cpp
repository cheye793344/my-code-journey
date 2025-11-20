#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 字典树节点
struct TrieNode {
    Stock* stock;
    vector<TrieNode*> children;

    TrieNode() : stock(nullptr), children(53, nullptr) {} // 26小写 + 26大写 + 1空格
};

// 字典树类
class TrieTree {
private:
    TrieNode* root;
    int searchCount;

    int getIndex(char ch) {
        if (ch >= 'a' && ch <= 'z') return ch - 'a';
        if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
        if (ch == ' ') return 52;
        return -1; // 非法字符
    }

    void collectStocks(TrieNode* node, vector<Stock*>& results) {
        if (node == nullptr) return;

        if (node->stock != nullptr) {
            results.push_back(node->stock);
        }

        for (int i = 0; i < 53; i++) {
            if (node->children[i] != nullptr) {
                collectStocks(node->children[i], results);
            }
        }
    }

public:
    TrieTree() : root(new TrieNode()), searchCount(0) {}

    void insert(const string& key, Stock* stock) {
        TrieNode* node = root;
        for (char ch : key) {
            int index = getIndex(ch);
            if (index == -1) continue;

            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->stock = stock;
    }

    vector<Stock*> prefixSearch(const string& prefix) {
        searchCount = 0;
        vector<Stock*> results;

        // 先找到前缀节点
        TrieNode* node = root;
        for (char ch : prefix) {
            searchCount++;
            int index = getIndex(ch);
            if (index == -1 || node->children[index] == nullptr) {
                return results;
            }
            node = node->children[index];
        }

        // 收集所有以该节点为根的股票
        collectStocks(node, results);
        return results;
    }

    int getSearchCount() const { return searchCount; }
};

void StockFunctions::trieSearchStock() {
    MenuSystem menu;
    system("cls");
    cout << "==========================================" << endl;
    cout << "     基于字典树的股票信息查找" << endl;
    cout << "==========================================" << endl;

    // 读取股票数据
    cout << "正在读取股票数据..." << endl;
    vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

    if (allStocks.empty()) {
        menu.showMessage("错误：无法读取股票数据文件或文件为空！");
        return;
    }

    // 构建字典树
    TrieTree trie;
    for (auto& stock : allStocks) {
        trie.insert(stock.englishName, &stock);
    }

    cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

    // 输入要查找的股票前缀
    string prefix = menu.getInput("请输入要查找的股票英文名称前缀: ");

    vector<Stock*> results = trie.prefixSearch(prefix);

    if (!results.empty()) {
        cout << "找到 " << results.size() << " 支匹配的股票:" << endl;
        for (Stock* stock : results) {
            cout << "------------------------------------------" << endl;
            stock->displayInfo();
        }

        // 计算ASL（简化处理）
        double totalLength = 0;
        for (const auto& stock : allStocks) {
            totalLength += stock.englishName.length();
        }
        double ASL = totalLength / allStocks.size();

        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    menu.showMessage(""); // 等待按键
}