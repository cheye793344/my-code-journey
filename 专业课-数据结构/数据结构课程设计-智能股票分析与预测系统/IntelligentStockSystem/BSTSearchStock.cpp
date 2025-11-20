#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 二叉排序树节点
struct BSTNode {
    Stock data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Stock& stock) : data(stock), left(nullptr), right(nullptr) {}
};

// 二叉排序树类
class BinarySearchTree {
private:
    BSTNode* root;
    int searchCount;

    BSTNode* insert(BSTNode* node, const Stock& stock) {
        if (node == nullptr) {
            return new BSTNode(stock);
        }

        if (stock.englishName < node->data.englishName) {
            node->left = insert(node->left, stock);
        }
        else if (stock.englishName > node->data.englishName) {
            node->right = insert(node->right, stock);
        }

        return node;
    }

    BSTNode* search(BSTNode* node, const string& sname) {
        if (node == nullptr) {
            return nullptr;
        }

        searchCount++;
        if (sname == node->data.englishName) {
            return node;
        }
        else if (sname < node->data.englishName) {
            return search(node->left, sname);
        }
        else {
            return search(node->right, sname);
        }
    }

    void destroy(BSTNode* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() : root(nullptr), searchCount(0) {}

    ~BinarySearchTree() {
        destroy(root);
    }

    void insert(const Stock& stock) {
        root = insert(root, stock);
    }

    Stock* search(const string& sname) {
        searchCount = 0;
        BSTNode* result = search(root, sname);
        return result ? &(result->data) : nullptr;
    }

    int getSearchCount() const { return searchCount; }

    void resetSearchCount() { searchCount = 0; }
};

// 计算ASL
double calculateBSTASL(BinarySearchTree& bst, const vector<Stock>& stocks) {
    if (stocks.empty()) return 0.0;

    int totalComparisons = 0;
    for (const auto& stock : stocks) {
        bst.search(stock.englishName);
        totalComparisons += bst.getSearchCount();
        bst.resetSearchCount();
    }

    return static_cast<double>(totalComparisons) / stocks.size();
}

void StockFunctions::BSTSearchStock() {
    MenuSystem menu;
    system("cls");
    cout << "==========================================" << endl;
    cout << "   基于二叉排序树的股票信息查找" << endl;
    cout << "==========================================" << endl;

    // 读取股票数据
    cout << "正在读取股票数据..." << endl;
    vector<Stock> stocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

    if (stocks.empty()) {
        menu.showMessage("错误：无法读取股票数据文件或文件为空！");
        return;
    }

    // 构建二叉排序树
    BinarySearchTree bst;
    for (const auto& stock : stocks) {
        bst.insert(stock);
    }

    cout << "数据读取完成！共读取 " << stocks.size() << " 支股票" << endl;

    // 输入要查找的股票英文名
    string sname = menu.getInput("请输入要查找的股票英文名称: ");

    Stock* foundStock = bst.search(sname);

    if (foundStock != nullptr) {
        cout << "查找成功！比较次数: " << bst.getSearchCount() << endl;
        foundStock->displayInfo();

        double ASL = calculateBSTASL(bst, stocks);
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    menu.showMessage(""); // 等待按键
}