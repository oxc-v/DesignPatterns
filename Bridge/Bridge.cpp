// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-18 17:57:58
// @LastEditTime: 2021-08-22 10:53:42
// @Description: 桥接模式的简单实现
// @FilePath: \Bridge\Bridge.cpp

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 定义实现类接口
class Implementation {
public:
    virtual ~Implementation() {}

    virtual string method() const = 0;
};

// 具体实现类
class ConcreteImplementationA : public Implementation
{
public:
    string method() const override {
        return "red";
    }
};

// 具体实现类
class ConcreteImplementationB : public Implementation
{
public:
    string method() const override {
        return "black";
    }
};

// 抽象类（与编程语言的抽象类无关）
class Abstraction
{
protected:
    std::shared_ptr<Implementation> implementation_;

public:
    Abstraction(std::shared_ptr<Implementation> implementation) : implementation_(implementation) {}

    virtual ~Abstraction() {}

    virtual string feature() const {
        return "I'm circle, my feature is " + implementation_->method();
    }
};

// 扩展基类（可选）
class ExtendedAbstraction : public Abstraction
{
public:
    ExtendedAbstraction(std::shared_ptr<Implementation> implementation) : Abstraction(implementation) {}

    string feature() const override {
        return "I'm retangle, my feature is " + implementation_->method();
    }
};

// 客户代码
void clientCode(const Abstraction& implementation)
{
    cout << implementation.feature() << endl;
}

int main(int argc, char* argv[])
{
    auto impl_A = std::make_shared<ConcreteImplementationA>();
    auto abstraction_1 = std::make_shared<Abstraction>(impl_A);
    auto extended_abstraction_1 = std::make_shared<ExtendedAbstraction>(impl_A);
    clientCode(*abstraction_1);
    clientCode(*extended_abstraction_1);

    auto impl_B = std::make_shared<ConcreteImplementationB>();
    auto abstraction_2 = std::make_shared<Abstraction>(impl_B);
    auto extended_abstraction_2 = std::make_shared<ExtendedAbstraction>(impl_B);
    clientCode(*abstraction_2);
    clientCode(*extended_abstraction_2);

    return 0;
}