#pragma once


///////////////// auto ////////////////////////////////////////////
/// auto���Ƶ���ָ�룬�����������õõ�ԭʼ����
/// auto�Ƶ����򣺲�����ָ������ã�auto�Ƶ����������cv�޶�������֮����Ϊָ�������ʱ��������cv�޶�����
/// ���зǾ�̬��Ա������ģ��������������� ������auto�Ƶ�����
/// 
/// ���˱�ʾiterator���߳����ͷ�֮�⣬auto��;��
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
	auto var = T::get(); /// ����Ӧ����auto����ʾvar���ͣ���Ϊ����ȷ��get()�ķ�������
}


///////////////// decltype ////////////////////////////////////////////
/// decltype��Ӧ���ڷ��ͱ����

#include <vector>

template <typename ContainerT>
class Foo1 {
public:
	void Func(ContainerT& container) {
		m_it = container.begin();
	}
private:
	typename ContainerT::iterator m_it;  /// �˴�����������
};

/// ��������m_it�������⣬������һ��const vectorʱ��m_it����Ӧ����ContainerT::const_iterator

int main() {
	using container = const std::vector<int>;
	container arr;
	Foo1<container> foo1;
	foo1.Func(arr); /// error
}


/// �������1���ػ���һ������const container��ģ���ࣺ

template <typename ContainerT>
class Foo1 <const ContainerT> {
public:
	void Func(const ContainerT& container) {  /// ����Ҫ����const�����������ƥ�䣨��const����ת��Ϊ��non const��
		m_it = container.begin();
	}
private:
	typename ContainerT::const_iterator m_it;
};



/// �������2��
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
/// auto���decltype�Լ����÷��������﷨�����Խ���������������������޷�ȷ��������

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
	return t + u;
}

/// �����������Ͳ���д�ɣ�
template<typename T, typename U>
decltype(t + u) add(T t, U u) {  /// error:����ֵ��ǰ���﷨��t uδ����
	return t + u;
}
/// ���Ͻ������
template<typename T, typename U>
decltype((*(T*)0)+ (*(U*)0)) add(T t, U u) {
	return t + u;
}


/// ʵ��2���޷��ù��Ϸ������
int foo(int& i);
float foo(float& i);

template<typename T>
auto func(T& val)->decltype(foo(val)) {
	return foo(val);
}