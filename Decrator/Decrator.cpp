// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-26 10:58:11
// @LastEditTime: 2021-08-26 21:18:20
// @Description: 装饰器模式的简单实现
// @FilePath: \Decrator\Decrator.cpp

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;

// 接口组件
class Component {
public:
    virtual ~Component() {}

    virtual string Operator() const = 0;
};

// 具体组件
class ConcreteComponent : public Component {
public:
    string Operator() const override { return "ConcreteComponent"; }
};

// 基础装饰器
class Decrator : public Component {
protected:
    shared_ptr<Component> component_;

public:
    Decrator(const shared_ptr<Component> component)
        : component_(component) {}

    virtual ~Decrator() {}

    string Operator() const override { return component_->Operator(); }
};

// 具体装饰器
class ConcreteDecrator1 : public Decrator {
public:
    ConcreteDecrator1(const shared_ptr<Component> component) 
        : Decrator(component) {}

    string Operator() const override { return "ConcreteComponent1 (" + Decrator::Operator() + ")"; }
};

// 具体装饰器
class ConcreteDecrator2 : public Decrator {
public:
    ConcreteDecrator2(const shared_ptr<Component> component) 
        : Decrator(component) {}

    string Operator() const override { return "ConcreteComponent2 (" + Decrator::Operator() + ")"; }
};

// 客户端代码
void ClientCode(const Component &component) {
    cout << "Result: " + component.Operator() << endl;
}

int main(int argc, char* argv[])
{
    cout << "Simple a component:\n";
    auto simple = make_shared<ConcreteComponent>();
    ClientCode(*simple);
    cout << "\n";

    // 无限套娃
    cout << "Decrated component:\n";
    auto decrator_1 = make_shared<ConcreteDecrator1>(simple);
    auto decrator_2 = make_shared<ConcreteDecrator2>(decrator_1);
    ClientCode(*decrator_2);

    return 0;
}