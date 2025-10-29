#include "Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>

std::string trim(std::string s) {
    auto notSpace = [](int ch) { return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s; std::getline(std::cin, s);
    return trim(s);
}

double readDoubleStrict(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        double v;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cout << "输入无效，请输入数字。\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDoubleOrNaN(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    line = trim(line);
    if (line.empty()) return std::numeric_limits<double>::quiet_NaN();
    try {
        std::size_t pos = 0;
        double v = std::stod(line, &pos);
        if (pos != line.size()) throw std::runtime_error("bad");
        return v;
    }
    catch (...) {
        std::cout << "输入无效，忽略该项修改。\n";
        return std::numeric_limits<double>::quiet_NaN();
    }
}
