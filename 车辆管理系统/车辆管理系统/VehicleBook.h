#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "Vehicle.h"

// 动态顺序表：初始容量 64；倍增扩容；Rule of Five；支持增删查改与模糊查询
class VehicleBook {
public:
    explicit VehicleBook(std::size_t initCap = 64);
    ~VehicleBook();
    VehicleBook(const VehicleBook& other);
    VehicleBook(VehicleBook&& other) noexcept;
    VehicleBook& operator=(VehicleBook other); // 拷贝-交换

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return cap_; }

    // CRUD
    int  findIndexByPlate(const std::string& plate) const;
    bool add(const Vehicle& v);
    bool removeByPlate(const std::string& plate);
    bool updateByPlate(const std::string& plate,
        const std::string* newPlate,
        const std::string* newModel,
        const double* newCapacity,
        const std::string* newDate);

    // 查询：按 车牌/型号 模糊匹配（大小写不敏感）
    std::vector<Vehicle> search(const std::string& key) const;

    const Vehicle& at(std::size_t i) const { return data_[i]; }

private:
    void   grow();   // 倍增扩容
    Vehicle* data_;
    std::size_t size_;
    std::size_t cap_;
};
