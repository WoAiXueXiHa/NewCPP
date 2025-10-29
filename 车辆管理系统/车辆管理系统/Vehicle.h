#pragma once
#include <string>

struct Vehicle {
    std::string plate;    // 车牌号（唯一键）
    std::string model;    // 车辆型号
    double      capacity; // 载重（吨）
    std::string buyDate;  // 购置日期：YYYY-MM-DD
};
