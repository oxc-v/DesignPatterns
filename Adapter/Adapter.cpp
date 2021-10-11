// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-18 10:30:28
// @LastEditTime: 2021-08-18 11:08:11
// @Description: 适配器模式的简单实现
// @FilePath: \Adapter\Adapter.cpp

#include <string>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 客户端所期待的接口
class Target
{
public:
    virtual ~Target() {}

    virtual string request() const {
        return "100";
    }
};

// 需要适配的类
class Adaptee
{
public:
    int specificRequest() const {
        return 100;
    }
};

// 适配器
class Adapter : public Target
{
private:
    Adaptee adaptee_;

public:
    Adapter(const Adaptee &adaptee) : adaptee_(adaptee) {}

    string request() const override {
        int n = adaptee_.specificRequest();
        
        return std::to_string(n);
    }
};

// 客户代码
void clientCode(const Target &target)
{
    cout << typeid(target.request()).name() << endl;
}

// 主函数
int main()
{
    Adaptee adaptee;
    cout << typeid(adaptee.specificRequest()).name() << endl;

    Adapter *adapter = new Adapter(adaptee);;
    clientCode(*adapter);

    return 0;
}