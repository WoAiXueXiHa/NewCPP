//// 常见API用法
//#include <string>
//#include <iostream>
//
//int main() {
//	std::string exmpleStr("Today");
//	std::string spliceStr(", happy!");
//	std::cout << "before splicing:" << std::endl;
//	std::cout << exmpleStr << std::endl;
//
//	// 拼接
//	exmpleStr += spliceStr;
//	std::cout << "after splicing:" << std::endl;
//	std::cout << exmpleStr << std::endl;
//
//	// 有效字符数
//	std::cout << exmpleStr.size() << std::endl;
//
//	// 查找字符 查找子串
//	std::cout << exmpleStr.find(',', 3) << std::endl; // 从索引为3的位置开始找字符','
//	std::cout << exmpleStr.find("happy", 2) << std::endl;// 从索引为2的位置开始找字符串"happy"
//
//	return 0;
//}

// mini_string_test.cpp
#include "mini_string.h"


// ======= 辅助打印函数 ========
static void print_header(const char* title) {
    cout << "===================== " << title << " =====================\n";
}

// ======= 构造 & 赋值 测试 ========
void test_constructors_and_assignment() {
    print_header("构造 & 赋值 测试");

    // 默认构造
    mini_string s0;
    cout << "s0 (default) size=" << s0.size() << " c_str=\"" << s0.c_str() << "\"\n";
    assert(s0.size() == 0);
    assert(strcmp(s0.c_str(), "") == 0);

    // C 字符串构造
    mini_string s1("Hello");
    cout << "s1 (from C-string) size=" << s1.size() << " c_str=\"" << s1.c_str() << "\"\n";
    assert(s1.size() == 5);
    assert(strcmp(s1.c_str(), "Hello") == 0);

    // 拷贝构造
    mini_string s2(s1);
    cout << "s2 (copy of s1) size=" << s2.size() << " c_str=\"" << s2.c_str() << "\"\n";
    assert(s2.size() == s1.size());
    assert(strcmp(s2.c_str(), s1.c_str()) == 0);

    // 赋值操作
    mini_string s3;
    s3 = s1;
    cout << "s3 (assigned from s1) c_str=\"" << s3.c_str() << "\"\n";
    assert(strcmp(s3.c_str(), "Hello") == 0);

    // 自赋值（不应崩溃）
    s1 = s1;
    cout << "s1 after self-assign: \"" << s1.c_str() << "\"\n";
    assert(strcmp(s1.c_str(), "Hello") == 0);

    cout << "构造与赋值测试通过\n\n";
}

// ======= 元素访问 测试 ========
void test_element_access() {
    print_header("元素访问 测试");

    mini_string s("abc");
    // operator[]
    assert(s[0] == 'a' && s[1] == 'b' && s[2] == 'c');

    // 修改通过 operator[]
    s[0] = 'x';
    cout << "after s[0] = 'x': " << s.c_str() << "\n";
    assert(strcmp(s.c_str(), "xbc") == 0);

    // front/back
    assert(s.front() == 'x');
    assert(s.back() == 'c');

    // at() 越界检查
    bool threw = false;
    try {
        char ch = s.at(100); // 预计抛出
        (void)ch;
    }
    catch (const std::out_of_range& e) {
        threw = true;
        cout << "at() 越界抛出: " << e.what() << "\n";
    }
    assert(threw);

    cout << "元素访问测试通过\n\n";
}

// ======= 容量 操作 测试 ========
void test_capacity_operations() {
    print_header("容量 操作 测试");

    mini_string s("12345");
    size_t old_cap = s.capacity();
    cout << "初始 size=" << s.size() << " capacity=" << old_cap << "\n";

    // reserve 扩容
    s.reserve(64);
    cout << "reserve(64) 后 capacity=" << s.capacity() << "\n";
    assert(s.capacity() >= 64);

    // clear & empty
    s.clear();
    cout << "clear 后 size=" << s.size() << " empty=" << (s.empty() ? "true" : "false") << "\n";
    assert(s.size() == 0 && s.empty());

    // 注意：shrink_to_fit 的实现可能与标准不一致，测试只保证不会崩溃且字符串正确
    s = mini_string("hello");
    size_t cap_before = s.capacity();
    s.reserve(100);
    s.shrink_to_fit(); // 调用以确保不会崩溃（实现细节可能不同）
    cout << "调用 shrink_to_fit() 后 size=" << s.size() << " capacity=" << s.capacity() << "\n";
    assert(strcmp(s.c_str(), "hello") == 0);

    cout << "容量操作测试通过\n\n";
}

void test_modification_operations() {
    print_header("修改操作 测试");

    // 1) push_back 与 += char
    mini_string s0 = "Today";
    const char ch_back = ',';
    s0 += ch_back;
    cout << s0 << endl;

    // 2) append C-string
    const char* str_back = "happy!";
    s0 += str_back;
    cout << s0 << endl;


    // 3) operator+=(mini_string)
    const mini_string s1 = "I like it!";
    s0 += s1;
    cout << s0 << endl;

    // 4) insert 单字符（开头）
    s0.insert(0, 'p');
    cout << s0 << endl;

    // 5) erase（删除已知范围）
    s0.erase(0, 3);
    cout << s0 << endl;
   
    // 6) clear
    s0.clear();
    cout << s0 << endl;

    cout << "修改操作测试通过\n\n";
}

void test_find_and_substr() {
    print_header("查找 & 截取 测试");

    // 测试字符串初始化
    mini_string s = "hello world hello";
    cout << "测试字符串: " << s << endl;

    // 1) 查找单个字符
    char target_char = 'w';
    size_t p1 = s.find(target_char);
    cout << "find('" << target_char << "') => " << p1 << "\n";
    assert(p1 != mini_string::npos);

    // 2) 查找子字符串
    const char* target_str = "hello";
    size_t p2 = s.find(target_str);
    cout << "find(\"" << target_str << "\") => " << p2 << "\n";
    assert(p2 == 0);

    // 3) 查找空字符串
    const char* empty_str = "";
    size_t p3 = s.find(empty_str);
    cout << "find(\"" << empty_str << "\") => " << p3 << " (expect 0)\n";
    assert(p3 == 0);

    // 4) 正常截取子字符串
    size_t pos1 = 6, len1 = 5;
    mini_string sub = s.substr(pos1, len1);
    cout << "substr(" << pos1 << "," << len1 << ") => \"" << sub.c_str() << "\"\n";
    assert(strcmp(sub.c_str(), "world") == 0);

    // 5) 截取超长长度的子字符串
    size_t pos2 = 6, len2 = 999;
    mini_string sub2 = s.substr(pos2, len2);
    cout << "substr(" << pos2 << "," << len2 << ") => \"" << sub2.c_str() << "\"\n";
    assert(strcmp(sub2.c_str(), "world hello") == 0);

    cout << "查找与截取测试通过\n\n";
}

// ======= 迭代器 & 范围 for 测试 ========
void test_iterators_and_rangefor() {
    print_header("迭代器 & 范围 for 测试");

    mini_string s("iter");
    // 通过迭代器读取
    string built;
    for (mini_string::iterator it = s.begin(); it != s.end(); ++it) {
        built.push_back(*it);
    }
    cout << "iterator read => \"" << built << "\"\n";
    assert(built == "iter");

    // 范围 for
    built.clear();
    for (auto ch : s) built.push_back(ch);
    cout << "range-for => \"" << built << "\"\n";
    assert(built == "iter");

    cout << "迭代器测试通过\n\n";
}

// ======= 其它边界 & 综合测试 ========
void test_misc_and_edge_cases() {
    print_header("其它边界 & 综合测试");

    // 空字符串 append / insert / erase
    mini_string s;
    s.append("");
    assert(s.size() == 0);
    s.insert(0, ""); // 插入空串
    assert(s.size() == 0);
    s.erase(0, 0);
    assert(s.size() == 0);

    // 长字符串拼接（触发多次扩容）
    mini_string longstr;
    const char* chunk = "0123456789";
    for (int i = 0; i < 100; ++i) longstr.append(chunk);
    cout << "longstr size=" << longstr.size() << "\n";
    assert(longstr.size() == (size_t)10 * 100);

    cout << "其它边界测试通过\n\n";
}

int main() {
    cout << "=== mini_string 单元测试开始 ===\n\n";

    test_constructors_and_assignment();
    test_element_access();
    test_capacity_operations();
    test_modification_operations();
    test_find_and_substr();
    test_iterators_and_rangefor();
    test_misc_and_edge_cases();

    cout << "全部测试通过 \n";
    return 0;
}

