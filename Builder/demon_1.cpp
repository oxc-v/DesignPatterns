// @Birth: created by oxc on 2021-08-03
// @Content: 生成器模式的简单实现

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

class Product1
{
public:
    vector<string> parts_;

public:
    void reset() {
        parts_.clear();
    }

    void getParts() const {
        cout << "Product1 parts: ";
        for (const auto &it: parts_)
            cout << it << " ";
        cout << endl;
    }
};

// Builder接口声明了创建产品的不同部分的方法
class Builder
{
public:
    virtual ~Builder() {}
    virtual void reset() = 0;
    virtual void buildStep1() = 0;
    virtual void buildStep2() = 0;
    virtual void buildStep3() = 0;
};

// 实现Builder接口
class ConcreteBuilder1 : public Builder
{
private:
    shared_ptr<Product1> result_;

public:
    ConcreteBuilder1() {
        reset();
    }

    void reset() override {
        result_ = std::make_shared<Product1>();
    }

    void buildStep1() override {
        result_->parts_.push_back("part1");
    }

    void buildStep2() override {
        result_->parts_.push_back("part2");
    }

    void buildStep3() override {
        result_->parts_.push_back("part3");
    }

    shared_ptr<Product1> getResult() {
        return result_;
    }
};

// 管理者负责调整产品各个部分的创建步骤顺序
class Director
{
private:
    shared_ptr<Builder> builder_;

public:
    void set_builder(const shared_ptr<Builder>& builder){
        builder_ = builder;
    }

    // 管理者可以使用相同的方法构建多个产品变体
    void make(const string &type) {
        if ("1" == type) {
            builder_->buildStep1();
        } else if ("2" == type) {
            builder_->buildStep1();
            builder_->buildStep2();
        } else {
            builder_->buildStep1();
            builder_->buildStep2();
            builder_->buildStep3();
        }
    }
};

// 客户代码
void clientCode(Director& director)
{
    auto builder1 = std::make_shared<ConcreteBuilder1>();
    director.set_builder(builder1);

    director.make("1");
    auto product1 = builder1->getResult();
    product1->getParts();
    product1->reset();

    director.make("2");
    auto product2 = builder1->getResult();
    product2->getParts();
    product2->reset();

    director.make("3");
    auto product3 = builder1->getResult();
    product3->getParts();
    product3->reset();
}

// 主函数
int main()
{
    Director director;
    clientCode(director);

    return 0;
}