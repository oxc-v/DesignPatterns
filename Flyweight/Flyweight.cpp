// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-08-31 09:34:06
// @LastEditTime: 2021-08-31 11:51:47
// @Description: 使用享元模式实现相同字体对象的重复使用
// @FilePath: \Flyweight\Flyweight.cpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <initializer_list>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// 字体的外在状态
struct FontUniqueState {
    string color_;  // 颜色
    string style_;  // 样式

    friend std::ostream& operator<<(std::ostream &os, const FontUniqueState &state) {
        return os << "[" << state.color_ << "," << state.style_ << "]";
    }
};

// 字体的内在状态
struct FontSharedState {
    string encoding_;  // 编码

    friend std::ostream& operator<<(std::ostream &os, const FontSharedState &state) {
        return os << "[" << state.encoding_ << "]";
    }
};

// 字体（享元对象）
class Font {
private:
    FontSharedState shared_state_;

public:
    // 内在状态只能通过构造方法进行初始化，
    // 不能在外部进行修改
    Font(const FontSharedState &shared_state)
        : shared_state_(shared_state) {}

    // 传递外在状态给享元对象
    void Show(const FontUniqueState &unique_state) {
        cout << "The font: " << shared_state_ << " + " << unique_state << endl;
        cout << "\n";
    }
};

// 字体工厂
// 用于管理字体对象的重复利用
class FontFactory {
private:
  std::unordered_map<string, Font> fonts_;

private:
    string GetKey(const FontSharedState &shared_state) const {
        return shared_state.encoding_ + "_";
    }

public:
    FontFactory(std::initializer_list<FontSharedState> shared_states) {
        for (const auto &state: shared_states) {
            const string key = GetKey(state);
            fonts_.insert(std::make_pair(std::move(key), std::move(Font(state))));
        }
    }

    Font& GetFont(const FontSharedState &shared_state) {
        const string key = GetKey(shared_state);

        if (fonts_.find(key) == fonts_.end()) {
            cout << "The is new font.\n";

            fonts_.insert(std::make_pair(std::move(key), std::move(Font(shared_state))));
        } else {
            cout << "The font is exsisting.\n";
        }

        return fonts_.find(key)->second;
    }

    void ListFonts() const {
        cout << "The font list:\n";
        
        for (const auto &font: fonts_)
            cout << font.first << endl;
    }
};

// 客户端代码
void ClientCode(FontFactory &factory, 
                const FontSharedState &shared_state, 
                const FontUniqueState &unique_state) {
    cout << "Client wants to add a font.\n";
    
    Font &font = factory.GetFont(shared_state);
    font.Show(unique_state);
}

int main(int argc, char* argv[])
{
    FontFactory factory({{"1"}, {"2"}, {"3"}});

    factory.ListFonts();
    cout << "\n";

    ClientCode(factory, {"1"}, {"red", "宋体"});
    ClientCode(factory, {"1"}, {"green", "雅黑"});

    ClientCode(factory, {"5"}, {"green", "雅黑"});
    ClientCode(factory, {"5"}, {"green", "雅黑"});

    return 0;
}