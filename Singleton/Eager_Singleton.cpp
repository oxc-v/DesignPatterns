// @Birth: created by oxc on 2021-08-07
// @Content: 饿汉式单例模式，

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

private:
    // 单例是不可分配的
    Singleton& operator=(const Singleton &single) = delete;

    // 单例是不可赋值的
    Singleton(const Singleton &single) = delete;

    // 由于全局静态对象的初始化顺序在不同的编译单元是不确定的，
    // 当其他编译单元的全局静态对象引用此静态对象时，可能得到一个
    // 还未初始化完毕的对象
    struct InstanceCreator {
        InstanceCreator() { Singleton::getInstance("oxc"); }
    };

    // 确保单例在main函数前初始化
    static InstanceCreator creator_;

public:
    // 测试
    string value() const {
        return value_;
    }

    // 获取单例
    static Singleton& getInstance(const string &value);
};

// 确保单例在main函数前初始化完毕
Singleton::InstanceCreator Singleton::creator_;

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

    return 0;
}