// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-01 14:03:01
// @LastEditTime: 2021-09-01 15:02:07
// @Description: 利用责任链模式实现相关请求的分发
// @FilePath: \Chain_Of_Responsibility\ChainOfResponsibility.cpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 声明一个通用的处理者接口
class Handler {
public:
    virtual ~Handler() {}

    virtual string HandleRequest(const string& request) const = 0;

    virtual std::shared_ptr<Handler> SetNext(const std::shared_ptr<Handler> handler) = 0;
};

// 默认处理者
class BaseHandler : public Handler {
private:
    std::shared_ptr<Handler> next_handler_;

public:
    BaseHandler(const BaseHandler &other) = delete;
    BaseHandler& operator=(const BaseHandler& other) = delete;

    BaseHandler()
        : next_handler_(nullptr) {}
    
    virtual std::shared_ptr<Handler> SetNext(const std::shared_ptr<Handler> handler) {
        this->next_handler_ = handler;

        // 返回Handler是方便这样使用：
        // mokey->SetNext(dog)->SetNext(pig)
        return handler;
    }

    // 默认处理者对请求不作任何处理
    // 负责将请求传递给下一个处理者
    virtual string HandleRequest(const string& request) const override {
        if (nullptr != next_handler_)
            return next_handler_->HandleRequest(request);

        return {};
    }
};

// 具体处理者
// 具体处理者可以选择处理请求，或者将请求传递给下一个处理者
class MonkeyHandler : public BaseHandler {
public:
    string HandleRequest(const string& request) const override {
        if ("Banana" == request) {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return BaseHandler::HandleRequest(request);
        }
    }
};

class SquirrelHandler : public BaseHandler {
public:
    string HandleRequest(const string& request) const override {
        if ("Nut" == request) {
            return "Squirrel: I'll eat the " + request + ".\n";
        } else {
            return BaseHandler::HandleRequest(request);
        }
    }
};

class DogHandler : public BaseHandler {
public:
    string HandleRequest(const string& request) const override {
        if ("MeatBall" == request) {
            return "Dog: I'll eat the " + request + ".\n";
        } else {
            return BaseHandler::HandleRequest(request);
        }
    }
};

// 客户端代码
void ClientCode(const Handler& handler) {
    const std::vector<string> foods = {"Nut", "Banana", "Coffee"};

    // 分发食物
    for (const auto& f: foods) {
        cout << "Client: Who wants a " << f << "?\n";

        const string result = handler.HandleRequest(f);
        if (false == result.empty()) {
            cout << result << "\n";
        } else {
            cout << f << " was left untouched.\n";
        }
    }
}

int main(int argc, char* argv[])
{
    auto monkey = std::make_shared<MonkeyHandler>();
    auto squirrel = std::make_shared<SquirrelHandler>();
    auto dog  = std::make_shared<DogHandler>();

    monkey->SetNext(squirrel)->SetNext(dog);

    ClientCode(*monkey);

    return 0;
}