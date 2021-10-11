// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-22 09:12:37
// @LastEditTime: 2021-09-22 11:03:44
// @Description: 备忘录模式的简单实现
// @FilePath: \Memento\Memento.cpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Memento接口提供了一种检索元数据的方法
class Memento {
public:
    virtual ~Memento() {}

    virtual string GetState() const = 0;
};

class ConcreteMemento : public Memento {
private:
    string state_;

public:
    explicit ConcreteMemento(const string& state)
        : state_(state) {}

    string GetState() const override { return state_; }
};

// 原发器
class Originator {
private:
    // 需要保存的属性
    string state_;

public:
    explicit Originator(const string& state)
        : state_(state) { cout << "My initial state is " + state_ << "\n"; }

    // 修改状态
    void DoSomething(const string& state) { this->state_ = state; }
        
    // 保存当前状态
    auto Save() const { return std::make_shared<ConcreteMemento>(state_); }

    // 返回到某个状态
    void Restore(const std::shared_ptr<Memento> m) {
        this->state_ = m->GetState();
        cout << "Originator: My state is change.\n";
    }

    // 获取当前状态
    void ShowState() const { cout << "Originator: My current state is " + this->state_ << "\n"; }
};

// 管理者
class Caretaker {
private:
    std::vector<std::shared_ptr<Memento>> mementos_;
    std::shared_ptr<Originator> originator_;

public:
    explicit Caretaker(const std::shared_ptr<Originator> originator) 
        : originator_(originator) {}

    // 备份
    void Backup() {
        cout << "Caretaker: Saving Originator's state...\n";
        mementos_.push_back(originator_->Save());
    }

    // 回滚
    void Undo() {
        if (0 == mementos_.size())
            return;

        auto memento = mementos_.back();
        mementos_.pop_back();
        originator_->Restore(memento);
    }

    void ShowMementos() {
        cout << "Caretaker: Here's the list of mementos:\n";

        for (const auto& m : mementos_)
            cout << m->GetState() << "\n";
    }
};

// 客户端代码
void ClientCode() {
    auto originator = std::make_shared<Originator>("on");
    auto caretaker = std::make_shared<Caretaker>(originator);

    originator->ShowState();
    caretaker->Backup();
    cout << "\n";

    originator->DoSomething("off");
    originator->ShowState();
    caretaker->Backup();
    cout << "\n";

    caretaker->ShowMementos();
    cout << "\n";

    originator->DoSomething("oxc");
    originator->ShowState();
    cout << "\n";
    
    caretaker->Undo();
    originator->ShowState();
    caretaker->ShowMementos();
}

int main(int argc, char* argv[])
{
    ClientCode();

    return 0;
}