// @Birth: created by oxc on 2021-08-10
// @Content: 懒汉式单例模式，

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 单例
class Singleton
{
protected:
    // 测试
    string value_;

    // 测试
    Singleton(const string& value): value_(value) {}

    // 单例是不可分配的
    Singleton& operator=(const Singleton &single) = delete;

    // 单例是不可赋值的
    Singleton(const Singleton &single) = delete;

public:
    // 测试
    string value() const {
        return value_;
    }

    // 获取单例
    static Singleton& getInstance(const string &value);
};

// 获取对单例访问的实例
Singleton& Singleton::getInstance(const string &value)
{
    // c++11以后局部静态对象是线程安全的，
    // 但在c++98需要加锁
    static Singleton instance(value);

    return instance;
}

// 主函数
int main()
{
    Singleton &p = Singleton::getInstance("cxj");
    cout << p.value() << endl;

    Singleton &p2 = Singleton::getInstance("oxc");
    cout << p2.value() << endl;

    return 0;
}