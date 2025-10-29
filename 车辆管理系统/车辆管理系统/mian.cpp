#include <iostream>
#include "VehicleBook.h"
#include "Utils.h"
#include "Seed.h"

// === UI 层：基于 VehicleBook 的交互 ===
static void addVehicleUI(VehicleBook& book) {
    std::cout << "\n--- 新增车辆 ---\n";
    std::string plate = readLine("车牌号：");
    if (plate.empty()) { std::cout << "车牌号不能为空。\n"; return; }
    std::string model = readLine("车辆型号：");
    double capacity = readDoubleStrict("载重（吨）：");
    std::string date = readLine("购置日期（YYYY-MM-DD）：");

    Vehicle v{ plate, model, capacity, date };
    if (book.add(v)) std::cout << "新增成功。\n";
    else std::cout << "新增失败：车牌已存在或内存不足。\n";
}

static void deleteVehicleUI(VehicleBook& book) {
    std::cout << "\n--- 删除车辆 ---\n";
    std::string plate = readLine("输入要删除的车牌号：");
    if (book.removeByPlate(plate)) std::cout << "删除成功。\n";
    else std::cout << "未找到该车牌。\n";
}

static void updateVehicleUI(VehicleBook& book) {
    std::cout << "\n--- 修改车辆 ---\n";
    std::string plate = readLine("输入要修改的车牌号：");
    std::string np = readLine("新车牌号（留空不改）：");
    std::string nm = readLine("新车辆型号（留空不改）：");
    double nc = readDoubleOrNaN("新载重（吨，留空不改）：");
    std::string nd = readLine("新购置日期（YYYY-MM-DD，留空不改）：");

    const std::string* p_np = np.empty() ? nullptr : &np;
    const std::string* p_nm = nm.empty() ? nullptr : &nm;
    const double* p_nc = std::isnan(nc) ? nullptr : &nc;
    const std::string* p_nd = nd.empty() ? nullptr : &nd;

    if (book.updateByPlate(plate, p_np, p_nm, p_nc, p_nd))
        std::cout << "修改完成。\n";
    else
        std::cout << "修改失败：车牌不存在或新车牌冲突。\n";
}

static void searchVehicleUI(const VehicleBook& book) {
    std::cout << "\n--- 查询车辆 ---\n";
    std::string key = readLine("输入关键字（按“车牌号/车辆型号”模糊匹配）：");
    if (key.empty()) { std::cout << "关键字不能为空。\n"; return; }

    auto res = book.search(key);
    if (res.empty()) { std::cout << "未找到匹配结果。\n"; return; }
    for (const auto& v : res) {
        std::cout << "-----------------------------\n";
        std::cout << "车牌号： " << v.plate << "\n";
        std::cout << "车辆型号： " << v.model << "\n";
        std::cout << "载重（吨）： " << v.capacity << "\n";
        std::cout << "购置日期： " << v.buyDate << "\n";
    }
}

static void listVehiclesUI(const VehicleBook& book) {
    std::cout << "\n--- 车辆列表（" << book.size() << "/" << book.capacity()
        << "，已预置50条，初始容量64，自动倍增扩容）---\n";
    if (book.size() == 0) { std::cout << "暂无数据。\n"; return; }
    for (std::size_t i = 0; i < book.size(); ++i) {
        const auto& v = book.at(i);
        std::cout << (i + 1) << ") " << v.plate
            << " | 型号: " << v.model
            << " | 载重(吨): " << v.capacity
            << " | 购置: " << v.buyDate << "\n";
    }
}

static void printMenu() {
    std::cout << "\n====== 车辆列表管理系统 ======\n";
    std::cout << "1. 新增车辆\n";
    std::cout << "2. 删除车辆\n";
    std::cout << "3. 修改车辆\n";
    std::cout << "4. 查询车辆（模糊匹配：车牌/型号）\n";
    std::cout << "5. 列出全部\n";
    std::cout << "9. 使用帮助（如何查询）\n";
    std::cout << "0. 退出\n";
    std::cout << "请选择：";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    VehicleBook book(64); // 初始容量 64
    seedDemoData(book);   // 预置 50 条

    std::cout << "已预置 50 条车辆数据到内存（容量 64）。\n";
    std::cout << "可直接选择【4. 查询车辆】进行模糊查询，或按【9】查看查询帮助。\n";

    while (true) {
        printMenu();
        int op;
        if (!(std::cin >> op)) {
            std::cout << "输入无效，请输入数字选项。\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 吃掉行尾

        switch (op) {
        case 1: addVehicleUI(book);    break;
        case 2: deleteVehicleUI(book); break;
        case 3: updateVehicleUI(book); break;
        case 4: searchVehicleUI(book); break;
        case 5: listVehiclesUI(book);  break;
        case 9: showHelp();            break;
        case 0:
            std::cout << "已退出，感谢使用。\n";
            return 0;
        default:
            std::cout << "无效选项，请重试。\n";
        }
    }
}
