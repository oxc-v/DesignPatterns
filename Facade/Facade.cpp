// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-29 09:49:30
// @LastEditTime: 2021-08-29 10:04:05
// @Description: 外观模式的简单实现
// @FilePath: \Facade\Facade.cpp

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 复杂子系统
class SubSystem1 {
public:
    string Operator() const { return "Go!\n"; }
};

// 复杂子系统
class SubSystem2 {
public:
    string Operator() const { return "Fire!\n"; }
};

// 外观
class Facade {
private:
    SubSystem1 s1_;
    SubSystem2 s2_;

public:
    string Operator1() const { return s1_.Operator() + s2_.Operator(); }

    string Operator2() const { return s2_.Operator() + s1_.Operator(); }
};

// 客户端代码
void ClientCode(const Facade &f) {
    cout << f.Operator1() << endl;
    cout << f.Operator2() << endl;
}

int main(int argc, char* argv[])
{
    Facade f;
    ClientCode(f);

    return 0;
}