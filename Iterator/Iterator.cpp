// @Author: oxc
// @LastEditors: oxc
// @Date: 2021-09-08 21:16:34
// @LastEditTime: 2021-09-14 19:41:04
// @Description: 使用迭代器模式对Vector容器二次封装
// @FilePath: \Iterator\Iterator.cpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// 迭代器
// 其中T表示容器中的数据类型，U表示容器类型
template <typename T, typename U>
class Iterator {
private:
    typename vector<T>::iterator node_;

public:
    Iterator(const typename vector<T>::iterator& x)
        : node_(x) { }

    Iterator(const Iterator<T, U>& x)
        : node_(x.node_) { }

    Iterator() = default;

    T& operator*() const { return *node_; }

    T* operator->() const { return &(this->operator*()); }

    Iterator operator++(int) {
        Iterator tmp = *this;
        node_++;

        return tmp;
    }

    bool operator!=(const Iterator<T, U>& x) const { return x.node_ != node_; }
};

// 容器
// T表示容器中的数据类型
template <typename T>
class Container {
private:
    vector<T> data_;

public:
    using iterator = Iterator<T, Container>;

public:
    void push_back(T value) { data_.push_back(value); }

    void pop_back() { data_.pop_back(); }

    iterator begin() { return Iterator<T, Container>(data_.begin()); }

    iterator end() { return Iterator<T, Container>(data_.end()); }
};

int main(int argc, char* argv[])
{
    Container<int> test;
    for (int i = 1; i <= 10; i++)
        test.push_back(i);

    Container<int>::iterator it;
    for (auto it = test.begin(); it != test.end(); it++)
        cout << *it << endl;


    return 0;
}