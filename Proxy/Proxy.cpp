// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-31 14:10:20
// @LastEditTime: 2021-08-31 15:17:21
// @Description: 利用代理模式实现简单的客户端访问控制
// @FilePath: \Proxy\Proxy.cpp

#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 服务实体通用接口
class ServiceInterface {
public:
    virtual ~ServiceInterface() {}

    virtual void Request() const = 0;
};

// 真实服务实体
class RealService : public ServiceInterface {
public:
    void Request() const override { cout << "Request successfully!\n"; }
};

// 代理服务实体
class Proxy : public ServiceInterface {
private:
    std::shared_ptr<ServiceInterface> real_service_;

private:
    bool CheckAccess(const bool &ok) const { return ok; }

    void LogAccess() const { cout << "Proxy: Logging the time of request.\n"; }

public:
    Proxy operator=(const Proxy &p) = delete;

    Proxy(const std::shared_ptr<RealService> real_service)
        : real_service_(std::make_shared<RealService>(*real_service)) {}

    void Request() const override { 
        if (true == CheckAccess(true)) {
            real_service_->Request();
            LogAccess();
        } else {
            cout << "Proxy: Can't request.\n";
        }
     }
};

// 客户端代码
void ClientCode(const ServiceInterface &s) {
    s.Request();
}

int main(int argc, char* argv[])
{
    auto real_service = std::make_shared<RealService>();
    ClientCode(*real_service);
    cout << "\n";

    auto proxy = std::make_shared<Proxy>(real_service);
    ClientCode(*proxy);

    return 0;
}