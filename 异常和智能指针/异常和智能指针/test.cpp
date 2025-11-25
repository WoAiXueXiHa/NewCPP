#include <iostream>
using namespace std;

//#include <cassert>
//void errorC() {
//	// 1. 错误码
//	int* arr = (int*)malloc(4 * sizeof(int));
//	if (arr == NULL) {
//		perror("malloc error:");
//		return;
//	}
//
//	// 2. assert
//	int num = 0;
//	assert(num != 0);
//
//}
//
//void division(double a, double b) {
//	if (b == 0)
//		throw logic_error("分母为零！\n");
//	cout << "结果: " << a / b << endl;
//}
//int main() {
//	try {
//		division(10, 0);
//	}
//	catch(const logic_error& e){
//		cout << "错误：" << e.what() << endl;
//	}
//
//	return 0;
//}

//void func1() {
//	throw "1111111";
//}
//
//int main() {
//	try {
//		func1();
//	}
//	catch (const char* errmsg) {
//		cout << "捕获到的异常:" << errmsg << endl;
//	}
//}

// 处理代码匹配最近的抛异常位置
//void func() {
//	throw out_of_range("越界！");
//}
//
//void Func() {
//	try {
//		func();
//	}
//	catch (const out_of_range& e) {
//		cout << "Func 捕获到的异常:" << e.what() << endl;
//	}
//}
//
//int main() {
//	try {
//		Func();
//	}
//	catch(const exception& e){
//		cout << "main 捕获到的异常：" << e.what() << endl;
//	}
//
//	return 0;
//}

// 异常对象拷贝
//void func() {
//	throw out_of_range("越界！");
//}
//int main() {
//	try {
//		func();
//	}
//	catch (const exception& e) {
//		cout << "exception 捕获:" << e.what() << endl;
//	}
//	return 0;
//}


//void func() {
//	throw 42;  // 抛出整数类型异常
//}
//
//int main() {
//	try {
//		func();
//	}
//	catch (...) {  // 捕获所有异常
//		std::cout << "Caught some exception" << std::endl;
//	}
//	return 0;
//}


//// 栈展开
//void func1() {
//    throw out_of_range("Out of range error in func1");  // 异常在 func1 中抛出
//}
//
//void func2() {
//    try {
//        func1();  // 异常从 func1 传递到 func2
//    }
//    catch (const out_of_range& e) {
//        cout << "Caught in func2: " << e.what() << endl;  // func2 捕获异常
//        throw;  // 重新抛出异常
//    }
//}
//
//int main() {
//    try {
//        func2();  // func2 捕获异常并重新抛出
//    }
//    catch (const exception& e) {
//        cout << "Caught in main: " << e.what() << endl;  // main 捕获异常并处理
//    }
//    return 0;
//}

//
//// 异常重新抛出
//double division(double a, double b) {
//	if (0 == b) {
//		throw "分母为零！";
//	}
//	return a / b;
//}
//
//void Func() {
//	// 如果发生分母为零抛出异常 但是arr还未释放
//	// 所以这里捕获了异常但不处理
//	// 把异常交给外界处理 捕获之后重新抛出去
//	int* arr = new int[10];
//	try {
//		cout << division(10.1,0) << endl;
//	}
//	catch (...) {
//		cout << "delete[]" << arr << endl;
//		delete[] arr;
//		throw;
//	}
//
//	cout << "delete[]" << arr << endl;
//	delete[] arr;
//}
//
//int main() {
//
//	try {
//		Func();
//	}
//	catch (const char* errmsg) {
//		cout << errmsg << endl;
//	}
//	return 0;
//}
// 异常规范
//// 这里表示这个函数会抛出A/B/C/D中的某种类型的异常
//void fun() throw(A，B，C，D);
//// 这里表示这个函数只会抛出bad_alloc的异常
//void* operator new (std::size_t size) throw (std::bad_alloc);
//// 这里表示这个函数不会抛出异常
//void* operator delete (std::size_t size, void* ptr) throw();
//// C++11 中新增的noexcept，表示不会抛异常
//thread() noexcept;
//thread(thread&& x) noexcept;
