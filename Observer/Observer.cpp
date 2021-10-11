// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-25 11:51:42
// @LastEditTime: 2021-09-25 15:42:50
// @Description: 观察者模式
// @FilePath: \Observer\Observer.cpp

#include <iostream>
#include <string>
#include <memory>
#include <list>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 观察者接口
class IObserver {
public:
    ~IObserver() {}

    virtual void Update(const string& message) const = 0;
};

// 通知者接口
class ISubject {
public:
    ~ISubject() {}

    virtual void Attach(const std::shared_ptr<IObserver> observer) = 0;

    virtual void Detach(std::shared_ptr<IObserver> observer) = 0;

    virtual void Notify() = 0;
};

// 具体通知者
class Subject : public ISubject {
private:
    std::list<std::shared_ptr<IObserver>> observers_;
    
    string message_;

private:
    // 通知所有观察者
    void Notify() override {
        for (const auto& c: observers_)
            c->Update(this->message_);
    }

public:
    // 添加观察者
    void Attach(const std::shared_ptr<IObserver> observer) override {
        observers_.push_back(observer);
    }

    // 移除观察者
    void Detach(std::shared_ptr<IObserver> observer) override {
        observers_.remove(observer);
    }

    void CreateMessage(const string& message) {
        this->message_ = message;
        this->Notify();
    }
};

// 具体观察者
class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
private:
    std::shared_ptr<ISubject> subject_;

public:
    // 获取更新信息
    void Update(const std::string& message) const override {
        cout << "Observer: A new message is available --> " << message << "\n";
    }

    // 订阅
    void Publish(std::shared_ptr<ISubject> subject) {
        this->subject_ = subject;
        this->subject_->Attach(shared_from_this());
    }

    // 取消订阅
    void RemoveMeFromTheList() {
        this->subject_->Detach(shared_from_this());
        cout << "Observer: Removed from the list.\n";
    }
};

// 客户端代码
void ClientCode() {
    auto subject = std::make_shared<Subject>();
    auto observer_1 = std::make_shared<Observer>();
    auto observer_2 = std::make_shared<Observer>();

    observer_1->Publish(subject);
    observer_2->Publish(subject);

    subject->CreateMessage("iphone12");
    observer_1->RemoveMeFromTheList();
    subject->CreateMessage("iphone13");
}

int main(int argc, char* argv[])
{
    ClientCode();

    return 0;
}