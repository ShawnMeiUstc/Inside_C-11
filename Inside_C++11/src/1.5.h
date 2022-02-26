#pragma once
#include <iostream>
#include <functional>

/////////std::bind & std::function//////////////

/// std::function可以同一方式处理函数、函数对象、函数指针等可调用对象，（包装它们，形成一个有统一形式的可调用对象）；
/// 但是对类的成员（函数）指针无法统一处理；
/// 需要和std::bind结合使用；
/// 
/// C++调用非静态的成员函数时，采用的是一种__thiscall的函数调用方式。采用这种调用方式，编译器在编译的时候，
/// 会在调用的函数形参表中增加一个指向调用该成员函数的指针，也就是我们经常说的this指针。
/// 所以所有类的成员函数其实都是和类绑定的，只是非静态函数的调用方式是__thiscall,需要通过类对象来调用
/// 
/// std::bind作用：将可调用对象与其参数一起绑定成一个仿函数；
///				  将多元可调用对象转换成一元或者（n-1）元，即只绑定部分参数；
///				  对非静态的类成员（函数）指针进行绑定需要指定其地址（和类绑定 &ClassType::FuncName）和对象地址（&classObj）
/// 
class Foo {
public:
	int m_i = 0;
	void output(int x, int y) {
		std::cout << x << " " << y << std::endl;
	}
};

int main() {
	Foo foo;
	std::function<void(int, int)>func_ptr = std::bind(&Foo::output, &foo, std::placeholders::_1, std::placeholders::_2);
	func_ptr(1, 2); // 1 2

	/// <summary>
	/// 绑定类的数据成员指针,将其变为一个可调用对象，注意返回类型应该为引用（左值）
	/// </summary>
	/// <returns></returns>
	std::function<int& (void)> data_ptr = std::bind(&Foo::m_i, &foo);
	data_ptr() = 100;
	std::cout << foo.m_i << std::endl; // 100
}