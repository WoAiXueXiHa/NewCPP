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
        double cap = 1.5 + (i % 10) * 0.5; // 1.5 ~ 6.0 ��

        int year = 2021 + (i % 5);
        int month = 1 + (i % 12);
        int day = 1 + (i % 28);
        char dateBuf[16];
        std::snprintf(dateBuf, sizeof(dateBuf), "%04d-%02d-%02d", year, month, day);

        book.add(Vehicle{ plate, model, cap, std::string(dateBuf) });
    }
}

void showHelp() {
    std::cout << "\n===== ʹ�ð�������ѯ�� =====\n";
    std::cout << "1) ��ѯ��ڣ����˵�ѡ��4. ��ѯ��������\n";
    std::cout << "2) ֧�֡����ƺ� / �����ͺš���ģ��ƥ�䣬��Сд�����С�\n";
    std::cout << "3) ʾ���ؼ��֣�\n";
    std::cout << "   - ������ǰ׺��PLT000   ��ƥ�� PLT00001, PLT00025 ...��\n";
    std::cout << "   - ��ȷ���ƣ�  PLT00018\n";
    std::cout << "   - ���ͺţ�    Model-3   ��  Van-2\n";
    std::cout << "4) ��ѯ������г������ƺš��ͺš����ء��������ڡ�\n";
    std::cout << "5) ���޽��������ؼ����Ƿ���ȷ������ؼ��֡�\n";
    std::cout << "============================\n";
}
