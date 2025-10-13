//#include "queue.h"
//#include "stack.h"
#include "priority_queue.h"
#include <initializer_list>


//int main() {
//	//// �󶥶� myLess return a < b
//	//Vect::priority_queue<int, std::vector<int>, Vect::myLess<int>> maxHeap;
//	//for (int arr : {5,3,1,6,20,12,60,999})
//	//	maxHeap.push(arr);
//	//std::cout << "�Ѷ���" << maxHeap.top() << std::endl;
//
//	//// С���� myGreater return a > b
//	//Vect::priority_queue<int, std::vector<int>, Vect::myGreater<int>> minHeap;
//	//for (int arr : {5, 3, 1, 6, 20, 12, 60, 999})
//	//	minHeap.push(arr);
//	//std::cout << "�Ѷ���" << minHeap.top() << std::endl;
//
//	//// -1 -10 -2 -6 -7 
//	//// ���վ���ֵС���� ������С������ ���ȫ����
//	//Vect::priority_queue<int, std::vector<int>, Vect::absLess<int>> absHeap;
//	//for (int arr : {-1, -10, -2, -6, -7})
//	//	absHeap.push(arr);
//	//std::cout << "�Ѷ���" << absHeap.top() << std::endl;
//	//for (size_t i = 0; i < absHeap.size(); i++)
//	//{
//	//	std::cout << absHeap[i] << " ";
//	//}
//	//return 0;
//
//	//// ���ַ������ȴ������ a.size() < b.size()
//	//Vect::priority_queue<std::string, std::vector<std::string>, Vect::strLess> strHeap;
//	//for (std::string strArr : {"nihao", "hhh", "1234", "1433223"})
//	//	strHeap.push(strArr);
//	//std::cout << "�Ѷ���" << strHeap.top() << std::endl;
//
//	return 0;
//}

int main() {
    Vect::priority_queue<Vect::StudentInfo,
        std::vector<Vect::StudentInfo>,
        Vect::structLess> structHeap;

    for (const Vect::StudentInfo& stu :
        std::initializer_list<Vect::StudentInfo>{
           {91,  "coke"},
           {50,  "hhh"},
           {100, "1234"},
           {100, "22"}
        }) {
        structHeap.push(stu);
    }

    std::cout << "�Ѷ���" << structHeap.top().score
        << " " << structHeap.top().name << std::endl;
    return 0;
}