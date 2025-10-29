#include "VehicleBook.h"
#include <new>
#include <iostream>
#include <cctype>
#include <algorithm>

VehicleBook::VehicleBook(std::size_t initCap)
    : data_(nullptr), size_(0), cap_(initCap ? initCap : 64) {
    data_ = new Vehicle[cap_];
}

VehicleBook::~VehicleBook() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    cap_ = 0;
}

VehicleBook::VehicleBook(const VehicleBook& other)
    : data_(new Vehicle[other.cap_]), size_(other.size_), cap_(other.cap_) {
    for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
}

VehicleBook::VehicleBook(VehicleBook&& other) noexcept
    : data_(other.data_), size_(other.size_), cap_(other.cap_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
}

VehicleBook& VehicleBook::operator=(VehicleBook other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
    return *this;
}

void VehicleBook::grow() {
    std::size_t newCap = (cap_ == 0 ? 64 : cap_ * 2);
    Vehicle* newBuf = new (std::nothrow) Vehicle[newCap];
    if (!newBuf) {
        std::cout << "ÄÚ´æ·ÖÅäÊ§°Ü£¬À©ÈÝÖÐÖ¹¡£\n";
        return;
    }
    for (std::size_t i = 0; i < size_; ++i) newBuf[i] = data_[i];
    delete[] data_;
    data_ = newBuf;
    cap_ = newCap;
}

int VehicleBook::findIndexByPlate(const std::string& plate) const {
    for (std::size_t i = 0; i < size_; ++i)
        if (data_[i].plate == plate) return static_cast<int>(i);
    return -1;
}

bool VehicleBook::add(const Vehicle& v) {
    if (findIndexByPlate(v.plate) != -1) return false; // Î¨Ò»ÐÔ
    if (size_ == cap_) grow();
    if (size_ == cap_) return false; // À©ÈÝÊ§°Ü
    data_[size_++] = v;
    return true;
}

bool VehicleBook::removeByPlate(const std::string& plate) {
    int idx = findIndexByPlate(plate);
    if (idx == -1) return false;
    data_[static_cast<std::size_t>(idx)] = data_[size_ - 1];
    --size_;
    return true;
}

bool VehicleBook::updateByPlate(const std::string& plate,
    const std::string* newPlate,
    const std::string* newModel,
    const double* newCapacity,
    const std::string* newDate) {
    int idx = findIndexByPlate(plate);
    if (idx == -1) return false;

    if (newPlate && !newPlate->empty() && *newPlate != plate) {
        if (findIndexByPlate(*newPlate) != -1) return false; // ³åÍ»
    }

    Vehicle& r = data_[static_cast<std::size_t>(idx)];
    if (newPlate && !newPlate->empty()) r.plate = *newPlate;
    if (newModel && !newModel->empty()) r.model = *newModel;
    if (newCapacity && !std::isnan(*newCapacity) && *newCapacity >= 0) r.capacity = *newCapacity;
    if (newDate && !newDate->empty())   r.buyDate = *newDate;
    return true;
}

std::vector<Vehicle> VehicleBook::search(const std::string& key) const {
    auto toLower = [](std::string s) {
        for (char& c : s) {
            unsigned char uc = static_cast<unsigned char>(c);
            c = static_cast<char>(std::tolower(uc));
        }
        return s;
        };
    std::vector<Vehicle> res;
    std::string k = toLower(key);
    for (std::size_t i = 0; i < size_; ++i) {
        std::string p = toLower(data_[i].plate);
        std::string m = toLower(data_[i].model);
        if (p.find(k) != std::string::npos || m.find(k) != std::string::npos)
            res.push_back(data_[i]);
    }
    return res;
}
