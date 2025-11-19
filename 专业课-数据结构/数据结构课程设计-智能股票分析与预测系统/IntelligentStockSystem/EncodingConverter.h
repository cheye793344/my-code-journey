#pragma once
#include <string>
#include <windows.h>
#include <iostream>

class EncodingConverter {
public:
    // UTF-8 转 GBK (用于读取头歌平台的数据文件)
    static std::string UTF8ToGBK(const std::string& utf8Str) {
        if (utf8Str.empty()) return "";

        int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
        if (len == 0) return "";

        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, len);

        len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len];
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);

        std::string result(str);
        delete[] wstr;
        delete[] str;

        return result;
    }

    // GBK 转 UTF-8 (如果需要写回头歌格式)
    static std::string GBKToUTF8(const std::string& gbkStr) {
        if (gbkStr.empty()) return "";

        int len = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
        if (len == 0) return "";

        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, wstr, len);

        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len];
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);

        std::string result(str);
        delete[] wstr;
        delete[] str;

        return result;
    }

    // 自动检测并转换文件读取（处理头歌UTF-8文件）
    static std::string autoConvert(const std::string& input) {
        // 简单检测：如果包含中文字符且长度异常，可能是UTF-8
        bool hasChinese = false;
        for (char c : input) {
            if (static_cast<unsigned char>(c) > 0x7F) {
                hasChinese = true;
                break;
            }
        }

        if (hasChinese && input.length() > 0) {
            return UTF8ToGBK(input);
        }
        return input;
    }
};