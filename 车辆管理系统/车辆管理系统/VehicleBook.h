#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "Vehicle.h"

// ��̬˳�����ʼ���� 64���������ݣ�Rule of Five��֧����ɾ�����ģ����ѯ
class VehicleBook {
public:
    explicit VehicleBook(std::size_t initCap = 64);
    ~VehicleBook();
    VehicleBook(const VehicleBook& other);
    VehicleBook(VehicleBook&& other) noexcept;
    VehicleBook& operator=(VehicleBook other); // ����-����

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

    // ��ѯ���� ����/�ͺ� ģ��ƥ�䣨��Сд�����У�
    std::vector<Vehicle> search(const std::string& key) const;

    const Vehicle& at(std::size_t i) const { return data_[i]; }

private:
    void   grow();   // ��������
    Vehicle* data_;
    std::size_t size_;
    std::size_t cap_;
};
