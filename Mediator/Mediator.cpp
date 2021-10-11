// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-15 09:27:11
// @LastEditTime: 2021-09-15 17:34:14
// @Description: 中介者模式的简单实现
// @FilePath: \Mediator\Mediator.cpp

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 中介者接口
class BaseComponent;
class Mediator {
public:
    virtual ~Mediator() {}

    virtual void Notify(std::shared_ptr<BaseComponent> c, const string& event) = 0;
};

// 基础组件
class BaseComponent {
protected:
    std::shared_ptr<Mediator> mediator_;

public:
    virtual ~BaseComponent() {}

    explicit BaseComponent(std::shared_ptr<Mediator> m = nullptr)
        : mediator_(m) {}

    void SetMediator(std::shared_ptr<Mediator> m) { mediator_ = m; }
};

class ComponentA : public BaseComponent, public std::enable_shared_from_this<ComponentA> {
public:
    void DoA() {
        cout << "ComponentA does A.\n";
        mediator_->Notify(shared_from_this(), "A");
    }

    void DoB() {
        cout << "ComponentA does B.\n";
        mediator_->Notify(shared_from_this(), "B");
    }
};

class ComponentB : public BaseComponent, public std::enable_shared_from_this<ComponentB> {
public:
    void DoC() {
        cout << "ComponentB does C.\n";
        mediator_->Notify(shared_from_this(), "C");
    }

    void DoD() {
        cout << "ComponentB does D.\n";
        mediator_->Notify(shared_from_this(), "D");
    }
};

// 具体的中介者
class ConcreteMediator : public Mediator, public std::enable_shared_from_this<ConcreteMediator> {
private:
    std::shared_ptr<ComponentA> ca_;
    std::shared_ptr<ComponentB> cb_;

public:
    ConcreteMediator(std::shared_ptr<ComponentA> ca, std::shared_ptr<ComponentB> cb) 
        : ca_(ca), 
          cb_(cb) {}

    void Notify(std::shared_ptr<BaseComponent> c, const string& event) override {
        if ("A" == event) {
            cout << "Mediator reacts on A and triggers following operations:\n";
            this->cb_->DoC();
        }

        if ("D" == event) {
            cout << "Mediator reacts on D and triggers following operations:\n";
            this->ca_->DoB();
            this->cb_->DoC();
        }
    }
};

// 客户端代码
void ClientCode() {
    auto ca = std::make_shared<ComponentA>();
    auto cb = std::make_shared<ComponentB>();
    auto mediator = std::make_shared<ConcreteMediator>(ca, cb);

    ca->SetMediator(mediator);
    cb->SetMediator(mediator);

    ca->DoA();
    cout << endl;
    cb->DoD();
}

int main(int argc, char* argv[])
{
    ClientCode();

    return 0;
}