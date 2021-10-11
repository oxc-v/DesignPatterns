// @Birth: created by oxc on 2021-08-02
// @Content: 抽象工厂模式的简单实现

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 系列产品中的特定产品必须有一个基础接口。
// 所有基于此产品的变体都必须实现这个接口
class AbstractProductA
{
public:
    virtual ~AbstractProductA() {}
    virtual string productStyle() const = 0;
};

// 产品变体需实现特定产品的基础接口
class ConreteProductA1 : public AbstractProductA
{
public:
    string productStyle() const override {
        return "ProductA1";
    }
};

// 产品变体需实现特定产品的基础接口
class ConreteProductA2 : public AbstractProductA
{
public:
    string productStyle() const override {
        return "ProductA2";
    }
};

// 系列产品中的特定产品必须有一个基础接口。
// 所有基于此产品的变体都必须实现这个接口
class AbstractProductB
{
public:
    virtual ~AbstractProductB() {}
    virtual string productStyle() const = 0;
    virtual void otherUsage(const AbstractProductA &collaborator) const = 0;
};

// 产品变体需实现特定产品的基础接口
class ConreteProductB1 : public AbstractProductB
{
public:
    string productStyle() const override {
        return "ProductB1";
    }

    void otherUsage(const AbstractProductA &collaborator) const override {
        if ("ProductA1" == collaborator.productStyle())
            cout << this->productStyle() + " collaborating with " + collaborator.productStyle() << endl;
        else
            cout << this->productStyle() + " can't collaborating with " + collaborator.productStyle() << endl;
    }
};

// 产品变体需实现特定产品的基础接口
class ConreteProductB2 : public AbstractProductB
{
public:
    string productStyle() const override {
        return "ProductB2";
    }

    void otherUsage(const AbstractProductA &collaborator) const override {
        if ("ProductA2" == collaborator.productStyle())
            cout << this->productStyle() + " collaborating with " + collaborator.productStyle() << endl;
        else
            cout << this->productStyle() + " can't collaborating with " + collaborator.productStyle() << endl;
    }
};

// 抽象工厂声明了一组能返回不同抽象产品的工厂方法。
// 这些抽象产品属于同一个系列，且在高层主题或概念上具有相关性。
// 同系列的产品通常能够相互搭配使用。
// 系列产品可有多个变体，但不同变体的产品不能搭配使用。
class AbstractFactory
{
public:
    virtual ~AbstractFactory() {}
    virtual AbstractProductA* createAbstractProductA() const = 0;
    virtual AbstractProductB* createAbstractProductB() const = 0;
};

// 具体工厂可生成属于同一变体的系列产品。
// 工厂会确保其创建的产品能相互搭配使用。
class ConcreteFactory1 : public AbstractFactory
{
public:
    virtual ~ConcreteFactory1() {}
    AbstractProductA* createAbstractProductA() const override {
        return new ConreteProductA1();
    }
    AbstractProductB* createAbstractProductB() const override {
        return new ConreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    virtual ~ConcreteFactory2() {}
    AbstractProductA* createAbstractProductA() const override {
        return new ConreteProductA2();
    }
    AbstractProductB* createAbstractProductB() const override {
        return new ConreteProductB2();
    }
};

// 客户代码
void clientCode(const AbstractFactory &f1, const AbstractFactory &f2)
{
    // 1系列产品
    std::unique_ptr<AbstractProductA> A1(f1.createAbstractProductA());
    std::unique_ptr<AbstractProductB> B1(f1.createAbstractProductB());

    // 2系列产品
    std::unique_ptr<AbstractProductA> A2(f2.createAbstractProductA());
    std::unique_ptr<AbstractProductB> B2(f2.createAbstractProductB());

    // 搭配使用
    B1->otherUsage(*A1);

    // 不同系列的产品不能搭配使用
    B1->otherUsage(*A2);
}

// 主函数
int main()
{
    const AbstractFactory& f1 = ConcreteFactory1();
    const AbstractFactory& f2 = ConcreteFactory2();
    clientCode(f1, f2);

    return 0;
}