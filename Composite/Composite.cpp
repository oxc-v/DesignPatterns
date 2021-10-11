// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-22 20:08:02
// @LastEditTime: 2021-08-22 23:58:28
// @Description: 组合模式的简单实现
// @FilePath: \Composite\Composite.cpp

#include <iostream>
#include <string>
#include <memory>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::shared_ptr;
using std::list;

// Component 接口声明了叶子对象和复合对象的共同操作
class Component {
protected:
    shared_ptr<Component> parent_;

public:
    virtual ~Component() {}

    // 复合对象可以添加和删除子对象，叶子对象无需实现这些操作
    virtual void Add(shared_ptr<Component> c) {}
    virtual void Remove(shared_ptr<Component> c) {}

    virtual string Operator() const = 0;

    virtual bool IsComposite() const { return false; }

    shared_ptr<Component> GetParent() const { return this->parent_; }

    void SetParent(const shared_ptr<Component> c) { this->parent_ = c; }
};

// 复合对象
class Composite : public Component, public std::enable_shared_from_this<Composite> {
private:
    list<shared_ptr<Component>> children_;

public:
    void Add(shared_ptr<Component> c) override {
        this->children_.push_back(c);
        c->SetParent(shared_from_this());
    }

    void Remove(shared_ptr<Component> c) override { 
        children_.remove(c);
        c->SetParent(nullptr);
    }

    bool IsComposite() const override {
        return true;
    }

    string Operator() const override {
        string result;
        for (const auto &c : children_) {
            result += c->Operator();

            if (c != children_.back())
                result += " + ";
        }

        return result;
    }
};

// 叶子对象
class Leaf : public Component {
private:
    string str_;

public:
    Leaf(const string &str) 
        : str_(str) {}

    string Operator() const override {
        return str_;
    }
};

// 客户端代码
void ClientCode(shared_ptr<Component> c) {
    cout << c->Operator() << endl;
}

void ClientCode(shared_ptr<Component> c1, shared_ptr<Component> c2) {
    if (true == c1->IsComposite())
        c1->Add(c2);

    cout << c1->Operator() << endl;
}

int main(int argc, char* argv[])
{
    // 一个叶子对象
    auto simple = std::make_shared<Leaf>("simple");
    cout << "Simple object:\n";
    ClientCode(simple);
    cout << "\n";

    // 构建一个组合树对象
    auto leaf1 = std::make_shared<Leaf>("leaf1");
    auto leaf2 = std::make_shared<Leaf>("leaf2");
    auto leaf3 = std::make_shared<Leaf>("leaf3");

    auto branch1 = std::make_shared<Composite>();
    branch1->Add(leaf1);
    branch1->Add(leaf2);
    cout << "Branch1 object:\n";
    ClientCode(branch1);
    cout << "\n";

    auto branch2 = std::make_shared<Composite>();
    branch2->Add(leaf3);
    cout << "Branch2 object:\n";
    ClientCode(branch2);
    cout << "\n";

    auto object_tree = std::make_shared<Composite>();
    cout << "Tree object:\n";
    object_tree->Add(branch1);
    ClientCode(object_tree, branch2);

    return 0;
}