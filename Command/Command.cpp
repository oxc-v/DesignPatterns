// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-05 15:24:40
// @LastEditTime: 2021-09-05 16:24:25
// @Description: 使用命令模式实现餐厅点餐过程
// @FilePath: \Command\Command.cpp

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 命令接受者，包含一些重要的业务逻辑
// 类似餐厅的厨师
class Receiver {
public:
    void DoSomething() const {
        cout << "Start cooking!\n";
    }
};

// 抽象命令类
class Command {
public:
    virtual ~Command(){}

    virtual void Execute() const = 0;
};

// 具体命令
// 例如烤肉命令、煮青菜命令
class ConcreteCommand : public Command {
private:
    std::shared_ptr<Receiver> receiver_;

public:
    ConcreteCommand(const ConcreteCommand& other) = delete;
    ConcreteCommand& operator=(const ConcreteCommand& other) = delete;

    ConcreteCommand(const std::shared_ptr<Receiver> receiver)
        : receiver_(receiver) {}

    void Execute() const override { 
        cout << "Fried green vegetables.\n";
        receiver_->DoSomething();
     }
};

// 命令触发者
// 类似服务员将订单递交后厨
class Invoker {
private:
    std::vector<std::shared_ptr<Command>> commands_;

public:
    void SetCommand(const std::shared_ptr<Command> command) { commands_.push_back(command); }

    void ExecuteCommand() { 
        for (const auto& command : commands_)
            command->Execute();
    }
};

// 客户端代码
void ClientCode(const std::shared_ptr<Command> command) {
    Invoker waiter;
    waiter.SetCommand(command);
    waiter.ExecuteCommand();
}

int main(int argc, char* argv[])
{
    auto receiver = std::make_shared<Receiver>();
    auto command = std::make_shared<ConcreteCommand>(receiver);

    ClientCode(command);

    return 0;
}