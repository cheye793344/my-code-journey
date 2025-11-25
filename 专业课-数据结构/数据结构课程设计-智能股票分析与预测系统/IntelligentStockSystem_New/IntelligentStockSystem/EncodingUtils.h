#pragma once
#include <string>
#include <windows.h>
#include <iostream>

// 编码转换工具类
class EncodingUtils {
public:
    // 将UTF-8字符串转换为GBK（用于Windows控制台输出）
    static std::string Utf8ToGbk(const std::string& strUtf8) {
        int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
        if (len == 0) return strUtf8;
        wchar_t* wstr = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wstr, len);

        len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
        if (len == 0) {
            delete[] wstr;
            return strUtf8;
        }
        char* strGbk = new char[len];
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, strGbk, len, NULL, NULL);

        std::string result(strGbk);
        delete[] wstr;
        delete[] strGbk;
        return result;
    }

    // 设置控制台输入输出代码页，尝试兼容
    static void SetupConsole() {
        // 设置控制台为 GBK，防止VS默认环境乱码
        SetConsoleOutputCP(936);
        SetConsoleCP(936);
    }
};