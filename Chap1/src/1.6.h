#pragma once
#include <iostream>
/////////lambda/////////////////////////

/// 按值捕获的lambda，捕获的瞬间就确定变量的值，之后外部发生修改对其无法产生影响;
/// 如果希望使用的值随着变量的变化而变化，那么就是用引用捕获
///

void func() {
	int a = 0;
	auto f = [=] {std::cout << a << std::endl; };
	auto g = [&] {std::cout << a << std::endl; };
	a++;
	f(); // 0
	g(); // 1
}

/// 如果需要修改按值捕获的外部变量，应该添加mutable关键字

void func1() {
	int a = 0;
	auto f = [=]() mutable {return a++; }; // OK
}


/// lambda表达式可以看成带有operator()的类，即仿函数；lambda捕获列表的捕获的任何外部变量都会变成
/// 该类的成员变量，因此一个有状态的lambda（捕获了外部变量）不能转化为一个普通的函数指针，而无状态的
/// lambda则可以转化为普通函数指针；


