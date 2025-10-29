#include <iostream>
#include "VehicleBook.h"
#include "Utils.h"
#include "Seed.h"

// === UI �㣺���� VehicleBook �Ľ��� ===
static void addVehicleUI(VehicleBook& book) {
    std::cout << "\n--- �������� ---\n";
    std::string plate = readLine("���ƺţ�");
    if (plate.empty()) { std::cout << "���ƺŲ���Ϊ�ա�\n"; return; }
    std::string model = readLine("�����ͺţ�");
    double capacity = readDoubleStrict("���أ��֣���");
    std::string date = readLine("�������ڣ�YYYY-MM-DD����");

    Vehicle v{ plate, model, capacity, date };
    if (book.add(v)) std::cout << "�����ɹ���\n";
    else std::cout << "����ʧ�ܣ������Ѵ��ڻ��ڴ治�㡣\n";
}

static void deleteVehicleUI(VehicleBook& book) {
    std::cout << "\n--- ɾ������ ---\n";
    std::string plate = readLine("����Ҫɾ���ĳ��ƺţ�");
    if (book.removeByPlate(plate)) std::cout << "ɾ���ɹ���\n";
    else std::cout << "δ�ҵ��ó��ơ�\n";
}

static void updateVehicleUI(VehicleBook& book) {
    std::cout << "\n--- �޸ĳ��� ---\n";
    std::string plate = readLine("����Ҫ�޸ĵĳ��ƺţ�");
    std::string np = readLine("�³��ƺţ����ղ��ģ���");
    std::string nm = readLine("�³����ͺţ����ղ��ģ���");
    double nc = readDoubleOrNaN("�����أ��֣����ղ��ģ���");
    std::string nd = readLine("�¹������ڣ�YYYY-MM-DD�����ղ��ģ���");

    const std::string* p_np = np.empty() ? nullptr : &np;
    const std::string* p_nm = nm.empty() ? nullptr : &nm;
    const double* p_nc = std::isnan(nc) ? nullptr : &nc;
    const std::string* p_nd = nd.empty() ? nullptr : &nd;

    if (book.updateByPlate(plate, p_np, p_nm, p_nc, p_nd))
        std::cout << "�޸���ɡ�\n";
    else
        std::cout << "�޸�ʧ�ܣ����Ʋ����ڻ��³��Ƴ�ͻ��\n";
}

static void searchVehicleUI(const VehicleBook& book) {
    std::cout << "\n--- ��ѯ���� ---\n";
    std::string key = readLine("����ؼ��֣��������ƺ�/�����ͺš�ģ��ƥ�䣩��");
    if (key.empty()) { std::cout << "�ؼ��ֲ���Ϊ�ա�\n"; return; }

    auto res = book.search(key);
    if (res.empty()) { std::cout << "δ�ҵ�ƥ������\n"; return; }
    for (const auto& v : res) {
        std::cout << "-----------------------------\n";
        std::cout << "���ƺţ� " << v.plate << "\n";
        std::cout << "�����ͺţ� " << v.model << "\n";
        std::cout << "���أ��֣��� " << v.capacity << "\n";
        std::cout << "�������ڣ� " << v.buyDate << "\n";
    }
}

static void listVehiclesUI(const VehicleBook& book) {
    std::cout << "\n--- �����б�" << book.size() << "/" << book.capacity()
        << "����Ԥ��50������ʼ����64���Զ��������ݣ�---\n";
    if (book.size() == 0) { std::cout << "�������ݡ�\n"; return; }
    for (std::size_t i = 0; i < book.size(); ++i) {
        const auto& v = book.at(i);
        std::cout << (i + 1) << ") " << v.plate
            << " | �ͺ�: " << v.model
            << " | ����(��): " << v.capacity
            << " | ����: " << v.buyDate << "\n";
    }
}

static void printMenu() {
    std::cout << "\n====== �����б����ϵͳ ======\n";
    std::cout << "1. ��������\n";
    std::cout << "2. ɾ������\n";
    std::cout << "3. �޸ĳ���\n";
    std::cout << "4. ��ѯ������ģ��ƥ�䣺����/�ͺţ�\n";
    std::cout << "5. �г�ȫ��\n";
    std::cout << "9. ʹ�ð�������β�ѯ��\n";
    std::cout << "0. �˳�\n";
    std::cout << "��ѡ��";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    VehicleBook book(64); // ��ʼ���� 64
    seedDemoData(book);   // Ԥ�� 50 ��

    std::cout << "��Ԥ�� 50 ���������ݵ��ڴ棨���� 64����\n";
    std::cout << "��ֱ��ѡ��4. ��ѯ����������ģ����ѯ���򰴡�9���鿴��ѯ������\n";

    while (true) {
        printMenu();
        int op;
        if (!(std::cin >> op)) {
            std::cout << "������Ч������������ѡ�\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �Ե���β

        switch (op) {
        case 1: addVehicleUI(book);    break;
        case 2: deleteVehicleUI(book); break;
        case 3: updateVehicleUI(book); break;
        case 4: searchVehicleUI(book); break;
        case 5: listVehiclesUI(book);  break;
        case 9: showHelp();            break;
        case 0:
            std::cout << "���˳�����лʹ�á�\n";
            return 0;
        default:
            std::cout << "��Чѡ������ԡ�\n";
        }
    }
}
