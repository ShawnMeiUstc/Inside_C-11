#pragma once
#pragma optimize (, "off")
#include <iostream>
#include <vector>

/// 纯右值：非引用返回的临时变量、表达时产生的临时变量、原始字面变量、lambda表达式等；
/// 将亡值：将要被移动的对象、T&&函数返回值、std::move返回值等；


/// universal reference: 只要在严格的T&&、auto&&这些推导类型下才是universal reference，任何一点附加条件都会使
/// 其失效而变成一个普通的右值引用
template<typename T>
void f0(T&& para); // universal reference

// 以下皆为rvalue reference：
template<typename T>
void f1(const T&& para);

template<typename T>
void f2(std::vector<T>&& para);

template<typename T>
class Test {
	Test(T&& para);
};


template<typename T>
void f3(Test<T>&& para);


/// 一个变量的类型 与 它本身是左值还是右值没有关系：
int x = 0;
int&& var1 = std::move(x); // var1是右值引用，var1变量本身是一个左值
auto&& var2 = var1; // var2是一个通用引用，绑定的var1是一个左值，所以var2类型是一个左值引用int&


/////////////////////////The Big Four( and a half)/////////////////////////////////////////////



class DumbArray {
public:
	// friend函数名字外围作用域不可见，可通过ADL查找到
	friend void swap(DumbArray& first, DumbArray& second) noexcept {
		std::swap(first.m_len, second.m_len);
		std::swap(first.m_array, second.m_array);
	}

	DumbArray(int length = 0) : m_len(length), m_array(m_len ? new int[m_len] : nullptr) {}
	DumbArray(const DumbArray& other) : m_len(other.m_len), m_array(m_len ? new int[m_len] : nullptr) {
		std::copy(other.m_array, other.m_array + m_len, m_array);
	}
	DumbArray(DumbArray&& other) noexcept : DumbArray() {
		swap(*this, other);
	}

	DumbArray& operator=(DumbArray other) {
		swap(*this, other);
		return *this;
	}
	/// 并不需要移动赋值函数，因为参数other如果要被初始化为一个右值，那么将调用移动构造函数，并不涉及资源的重新分配

	~DumbArray() {
		delete[] m_array;
	}

private:
	int m_len;
	int* m_array;
};

////////////////////////////std::move////////////////////////////////////
/// std::move 并不会真正地移动对象，真正的移动操作是在移动构造函数、移动赋值函数等完成的，
/// std::move 只是将参数转换为右值引用而已（相当于一个 static_cast）。
/// 
/// 在函数内部的形参，即使它被声明为右值引用类型，并被绑定一个右值引用类型的实参，
/// 但它本身仍然是左值，无法由它触发移动XX函数，除非对它再次使用move函数或者forward函数。
/// 
std::string str = "test";
std::string&& r = std::move(str);
std::string t(r); // 这里r本身是一个左值，只会出发拷贝构造函数


//////////////////////////std::move 与 std::forward////////////////////////////////////

template <typename T>
typename std::remove_reference<T>::type&& move(T&& t)
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}


template <typename T>
T&& forward(typename std::remove_reference<T>::type& param)
{
	return static_cast<T&&>(param);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type&& param)
{
	return static_cast<T&&>(param);
}


//////////////////////////////////////万能的wrapper////////////////////////////////////////////


template<typename Func, typename ... Args>
inline auto FuncWrapper(Func&& func, Args&& ... args) -> decltype(func(std::forward<Args>(args)...)) {
	return func(std::forward<Args>(args)...);
}