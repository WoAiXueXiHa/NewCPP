#include "Seed.h"
#include <cstdio>
#include <string>
#include <iostream>

void seedDemoData(VehicleBook& book) {
    const std::string models[] = { "Model-1", "Model-2", "Model-3", "Truck-1", "Truck-2", "Van-1", "Van-2" };
    for (int i = 1; i <= 50; ++i) {
        char plateBuf[16];
        std::snprintf(plateBuf, sizeof(plateBuf), "PLT%05d", i); // PLT00001 ~ PLT00050
        std::string plate = plateBuf;

        std::string model = models[i % (sizeof(models) / sizeof(models[0]))];
        double cap = 1.5 + (i % 10) * 0.5; // 1.5 ~ 6.0 吨

        int year = 2021 + (i % 5);
        int month = 1 + (i % 12);
        int day = 1 + (i % 28);
        char dateBuf[16];
        std::snprintf(dateBuf, sizeof(dateBuf), "%04d-%02d-%02d", year, month, day);

        book.add(Vehicle{ plate, model, cap, std::string(dateBuf) });
    }
}

void showHelp() {
    std::cout << "\n===== 使用帮助（查询） =====\n";
    std::cout << "1) 查询入口：主菜单选择【4. 查询车辆】。\n";
    std::cout << "2) 支持“车牌号 / 车辆型号”的模糊匹配，大小写不敏感。\n";
    std::cout << "3) 示例关键字：\n";
    std::cout << "   - 按车牌前缀：PLT000   （匹配 PLT00001, PLT00025 ...）\n";
    std::cout << "   - 精确车牌：  PLT00018\n";
    std::cout << "   - 按型号：    Model-3   或  Van-2\n";
    std::cout << "4) 查询结果会列出：车牌号、型号、载重、购置日期。\n";
    std::cout << "5) 若无结果，请检查关键字是否正确或更换关键字。\n";
    std::cout << "============================\n";
}
