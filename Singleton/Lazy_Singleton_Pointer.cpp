// @Birth: created by oxc on 2021-08-10
// @Content: 懒汉式单例模式，使用智能指针实现

#include <iostream>
#include <string>
#include <mutex>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::mutex;
using std::string;
using std::shared_ptr;
using std::make_shared;

// 使用智能指针实现懒汉式单例
class Singleton
{
private:
    // 测试
    string value_;

    // 全局节点
    static shared_ptr<Singleton> instance_;

    // 同步锁
    static mutex mutex_;

protected:
    // 测试
    Singleton(const string& value): value_(value) {}

    // 单例是不可分配的
    Singleton& operator=(const Singleton &single) = delete;

    // 单例是不可赋值的
    Singleton(const Singleton &single) = delete;

public:
    // 测试
    string value() const {
        return value_;
    }

    // 获取单例
    // make_shared 无法调用私有构造函数
    template <typename... Args>
    static shared_ptr<Singleton> getInstance(Args&&... args) {
        struct EnableMakeShared : public Singleton {
            EnableMakeShared(Args&&... args) : Singleton(std::forward<Args>(args)...) {}
        };
        
        // 双重检测，避免没必要的加锁
        if (instance_ == nullptr) {
            // std::lock_guard对象构造时，自动调用mtx.lock()进行上锁
            // std::lock_guard对象析构时，自动调用mtx.unlock()释放锁
            std::lock_guard<mutex> lock(mutex_);
            if (instance_ == nullptr) {
                instance_ = std::static_pointer_cast<Singleton>(make_shared<EnableMakeShared>(std::forward<Args>(args)...));
            }
        }

        return instance_;
    }
};

// 全局节点
shared_ptr<Singleton> Singleton::instance_ = nullptr;

// 同步锁
mutex Singleton::mutex_;

// 主函数
int main()
{
    auto p = Singleton::getInstance("cxj");
    cout << p->value() << endl;

    auto p2 = Singleton::getInstance("oxc");
    cout << p2->value() << endl;

    return 0;
}