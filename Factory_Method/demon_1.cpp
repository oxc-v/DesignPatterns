// @Birth: created by oxc on 2021-08-01
// @Content: 工厂方法模式的简单实现

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
 * Product是一个接口类，不能直接实例化。
 * Product接口声明了所有具体产品必须执行的操作。
 */

class Product
{
public:
    virtual ~Product(){};
    virtual string doSomething() const = 0;
};

/* ConcreteProductA提供了Product接口的各种具体实现 */

class ConcreteProductA : public Product
{
public:
    string doSomething() const override
    {
        return "ConcreteProductA";
    }
};

class ConcreteProductB : public Product
{
public:
    string doSomething() const override
    {
        return "ConcreteProductB";
    }
};

/* Creator是一个抽象基类
 * Creator包含一个工厂方法，改方法返回一个Product对象
 */

class Creator
{
public:
    virtual ~Creator(){};
    virtual Product *createProduct() const = 0;

    virtual string someOperation()
    {
        Product *product = this->createProduct();
        string result = "The creator work with " + product->doSomething();
        delete product;
        return result;
    }
};

/* 具体创建者覆盖工厂方法以更改结果产品的类型。 */

class ConcreteCreatorA : public Creator
{
public:
    Product *createProduct() const override
    {
        return new ConcreteProductA;
    }
};

class ConcreteCreatorB : public Creator
{
public:
    Product *createProduct() const override
    {
        return new ConcreteProductB;
    }
};

/* 客户代码 */

void clientCode(Creator& creator)
{
    cout << creator.someOperation() << endl;
}

// 主函数

int main()
{
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator *creator1 = new ConcreteCreatorA;
    clientCode(*creator1);

    cout << endl;

    cout << "App: Launched with the ConcreteCreator2.\n";
    Creator *creator2 = new ConcreteCreatorB;
    clientCode(*creator2);

    delete creator1;
    delete creator2;

    return 0;
}