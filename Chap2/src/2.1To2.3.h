#pragma once
#pragma optimize (, "off")
#include <iostream>
#include <vector>

/// ����ֵ�������÷��ص���ʱ���������ʱ��������ʱ������ԭʼ���������lambda���ʽ�ȣ�
/// ����ֵ����Ҫ���ƶ��Ķ���T&&��������ֵ��std::move����ֵ�ȣ�


/// universal reference: ֻҪ���ϸ��T&&��auto&&��Щ�Ƶ������²���universal reference���κ�һ�㸽����������ʹ
/// ��ʧЧ�����һ����ͨ����ֵ����
template<typename T>
void f0(T&& para); // universal reference

// ���½�Ϊrvalue reference��
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


/// һ������������ �� ����������ֵ������ֵû�й�ϵ��
int x = 0;
int&& var1 = std::move(x); // var1����ֵ���ã�var1����������һ����ֵ
auto&& var2 = var1; // var2��һ��ͨ�����ã��󶨵�var1��һ����ֵ������var2������һ����ֵ����int&


/////////////////////////The Big Four( and a half)/////////////////////////////////////////////



class DumbArray {
public:
	// friend����������Χ�����򲻿ɼ�����ͨ��ADL���ҵ�
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
	/// ������Ҫ�ƶ���ֵ��������Ϊ����other���Ҫ����ʼ��Ϊһ����ֵ����ô�������ƶ����캯���������漰��Դ�����·���

	~DumbArray() {
		delete[] m_array;
	}

private:
	int m_len;
	int* m_array;
};

////////////////////////////std::move////////////////////////////////////
/// std::move �������������ƶ������������ƶ����������ƶ����캯�����ƶ���ֵ��������ɵģ�
/// std::move ֻ�ǽ�����ת��Ϊ��ֵ���ö��ѣ��൱��һ�� static_cast����
/// 
/// �ں����ڲ����βΣ���ʹ��������Ϊ��ֵ�������ͣ�������һ����ֵ�������͵�ʵ�Σ�
/// ����������Ȼ����ֵ���޷����������ƶ�XX���������Ƕ����ٴ�ʹ��move��������forward������
/// 
std::string str = "test";
std::string&& r = std::move(str);
std::string t(r); // ����r������һ����ֵ��ֻ������������캯��


//////////////////////////std::move �� std::forward////////////////////////////////////

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


//////////////////////////////////////���ܵ�wrapper////////////////////////////////////////////


template<typename Func, typename ... Args>
inline auto FuncWrapper(Func&& func, Args&& ... args) -> decltype(func(std::forward<Args>(args)...)) {
	return func(std::forward<Args>(args)...);
}