// @Birth: created by oxc on 2021-08-04
// @Content: 原型注册表的简单实现

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::unique_ptr;
using std::unordered_map;

// 具有克隆能力的基础原型
class Prototype
{
protected:
    string name_;

public:
    Prototype(const string &name) : name_(name) {}
    virtual ~Prototype() {}
    virtual unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

// 具体原型
class ConcretePrototype1 : public Prototype
{
public:
    ConcretePrototype1(const string &name) : Prototype(name) {}

    unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype1>(*this);
    }

    void print() const override {
        cout << name_ << endl;
    }
};

// 具体原型
class ConcretePrototype2 : public Prototype
{
public:
    ConcretePrototype2(const string &name) : Prototype(name) {}

    unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype2>(*this);
    }

    void print() const override {
        cout << name_ << endl;
    }
};

// 原型注册工厂
class PrototypeFactory
{
private:
    unordered_map<string, unique_ptr<Prototype>> items_;

public:
    void addItem(const string &id, unique_ptr<Prototype> p) {
        bool ok = items_.insert({id, std::move(p)}).second;
        if (false == ok)
            cout << "insert error!\n";
    }

    void removeItem(const string &id) {
        int ok = items_.erase(id);
        if (0 == ok)
            cout << "erase error!\n";
    }

    unique_ptr<Prototype> createPrototype(const string &id) {
        auto it = items_.find(id);
        if (items_.end() == it) {
            cout << "createPrototype error!\n";
            exit(1);
        } else {
            return it->second->clone();
        }
    }
};

// 客户代码
void clientCode(PrototypeFactory &factory)
{
    factory.addItem("1", std::make_unique<ConcretePrototype1>("oxc"));
    factory.addItem("2", std::make_unique<ConcretePrototype2>("cxj"));

    auto p1 = factory.createPrototype("1");
    p1->print();

    auto p2 = factory.createPrototype("2");
    p2->print();
}


// 主函数
int main()
{
    PrototypeFactory f;
    clientCode(f);

    return 0;
}