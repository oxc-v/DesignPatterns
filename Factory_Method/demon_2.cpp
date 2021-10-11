// @Birth: created by oxc on 2021-08-01
// @Content: 工厂方法模式的简单实现

#include <iostream>
#include <string>
#include <memory>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

/* 产品接口中将声明所有具体产品都必须实现的操作。 */

class Button
{
public:
    virtual ~Button(){};
    virtual void render() const = 0;
    virtual void onClicked() const = 0;
};

/* 具体产品需提供产品接口的各种实现。 */

class WindowsButton : public Button
{
public:
    void render() const override
    {
        cout << "This is a Windows button.\n";
    }

    void onClicked() const override
    {
        cout << "The Windows button is clicked.\n";
    }
};

class LinuxButton : public Button
{
public:
    void render() const override
    {
        cout << "This is a Linux button.\n";
    }

    void onClicked() const override
    {
        cout << "The Linux button is clicked.\n";
    }
};

/*
 * 创造者类声明的工厂方法必须返回一个产品类的对象。
 */

class Dialog
{
public:
    virtual ~Dialog() {}
    virtual Button* createButton() const = 0;

    /*
     * 创造者的主要职责并非是创建产品。
     * 其中通常会包含一些核心业务逻辑，这些逻辑依赖与由工厂方法返回的产品对象。
     */
    virtual void render()
    {
        std::unique_ptr<Button> btn(this->createButton());
        btn->render();
        btn->onClicked();
    }
};

/* 具体创建者将重写工厂方法以改变其所返回的产品类型。 */

class WindowsDialog : public Dialog
{
public:
    Button* createButton() const override
    {
        return new WindowsButton();
    }
};

class LinuxDialog : public Dialog
{
public:
    Button* createButton() const override
    {
        return new LinuxButton();
    }
};

/* 客户端代码 */

void readAppplicationConfig(const string &os)
{
    std::unique_ptr<Dialog> dlg;

    if (os == "Windows")
        dlg = std::make_unique<WindowsDialog>();
    else if (os == "Linux")
        dlg = std::make_unique<LinuxDialog>();
    else
        throw string("Error! Unknown operating system!");

    dlg->render();
}

/* 主函数 */

int main()
{
    try {
        // Windows
        readAppplicationConfig("Windows");

        // Linux
        readAppplicationConfig("Linux");

        // Unknown os
        readAppplicationConfig("HongMong");
    } catch (const string &ex) {
        std::cerr << ex;
    }

    return 0;
}