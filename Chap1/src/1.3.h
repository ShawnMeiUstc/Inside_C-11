#pragma once
#include <initializer_list>

/////////////初始化列表//////////////////////////////

/// C++11初始化列表使用的范围被大大增加，可以统一使用一种初始化方式，只是要注意聚合类与非聚合类的区别
/// 聚合类：无用户自定义构造函数；无私有或受保护的非静态数据成员；无基类、无虚函数；无{}和=直接初始化的非静态数据成员；
/// 对聚合类使用列表初始化相当于对每个成员直接赋值，而对非聚合类则是调用它的构造函数来初始化；
struct  A {
	int x;
	int y;
};

struct B {
	int x;
	int y;
	B(int, int) : x(0), y(0) {}
};

A a{ 123,456 }; // a.x = 123, a.y = 456
B b{ 123, 456}; // b.x = 0, b.y = 0 因为调用了B的构造函数初始化


///使用std::initializer_list<T>形式作为参数的函数可以接受任意长度的T类型的实参，用{}传参
/// 
/// initializer_list不保存初始化列表中的元素拷贝，而只是存储其引用，因而不能作为拷贝容器使用；
std::initializer_list<int> func() // wrong：返回a b的值已经不确定，应该返回std::vector<int>或其他保存拷贝的容器
{
	int a = 1;
	int b = 2;
	return { a, b };
}

/// 列表初始化可以防止窄化转换
int a = 1.1;
int b = { 1.1 }; // error