#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "EncodingConverter.h"

class FileReader {
public:
    // 读取文件内容，自动处理编码
    static std::vector<std::string> readFile(const std::string& filename) {
        std::vector<std::string> lines;
        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open()) {
            std::cout << "错误: 无法打开文件 " << filename << std::endl;
            return lines;
        }

        std::string line;
        while (std::getline(file, line)) {
            // 自动编码转换
            std::string convertedLine = EncodingConverter::autoConvert(line);
            lines.push_back(convertedLine);
        }

        file.close();
        return lines;
    }

    // 写入文件（使用本地编码）
    static bool writeFile(const std::string& filename, const std::vector<std::string>& lines) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        for (const auto& line : lines) {
            file << line << std::endl;
        }

        file.close();
        return true;
    }
};