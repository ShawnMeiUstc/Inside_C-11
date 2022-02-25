#pragma once


///////////////// auto ////////////////////////////////////////////
/// auto能推导出指针，但会抛弃引用得到原始类型
/// auto推导规则：不声明指针或引用，auto推导结果将抛弃cv限定符，反之声明为指针或引用时，将保持cv限定符；
/// 类中非静态成员变量、模板参数、函数参数 不能用auto推导类型
/// 
/// 除了表示iterator等冗长类型符之外，auto用途：

class Foo0 {
public:
	static int get() {
		return 0;
	}
};

class Bar0 {
public:
	static const char* get() {
		return "0";
	}
};

template<typename T>
void func() {
	auto var = T::get(); /// 这里应该用auto来表示var类型，因为还不确定get()的返回类型
}


///////////////// decltype ////////////////////////////////////////////
/// decltype常应用于泛型编程中

#include <vector>

template <typename ContainerT>
class Foo1 {
public:
	void Func(ContainerT& container) {
		m_it = container.begin();
	}
private:
	typename ContainerT::iterator m_it;  /// 此处定义有问题
};

/// 上述定义m_it处有问题，当传入一个const vector时，m_it类型应该是ContainerT::const_iterator

int main() {
	using container = const std::vector<int>;
	container arr;
	Foo1<container> foo1;
	foo1.Func(arr); /// error
}


/// 解决方法1：特化出一个接受const container的模板类：

template <typename ContainerT>
class Foo1 <const ContainerT> {
public:
	void Func(const ContainerT& container) {  /// 这里要加上const，否则参数不匹配（把const参数转化为了non const）
		m_it = container.begin();
	}
private:
	typename ContainerT::const_iterator m_it;
};



/// 解决方法2：
template <typename ContainerT>
class Foo2 {
public:
	void Func(ContainerT& container) {
		m_it = container.begin();
	}
private:
	decltype(ContainerT.begin()) m_it;
};


///////////////// auto + decltype ////////////////////////////////////////////
/// auto配合decltype以及后置返回类型语法，可以解决返回类型依赖参数而无法确定的问题

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
	return t + u;
}

/// 上述返回类型不可写成：
template<typename T, typename U>
decltype(t + u) add(T t, U u) {  /// error:返回值是前置语法，t u未定义
	return t + u;
}
/// 古老解决法：
template<typename T, typename U>
decltype((*(T*)0)+ (*(U*)0)) add(T t, U u) {
	return t + u;
}


/// 实例2：无法用古老方法解决
int foo(int& i);
float foo(float& i);

template<typename T>
auto func(T& val)->decltype(foo(val)) {
	return foo(val);
}