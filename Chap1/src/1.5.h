#pragma once
#include <iostream>
#include <functional>

/////////std::bind & std::function//////////////

/// std::function����ͬһ��ʽ���������������󡢺���ָ��ȿɵ��ö��󣬣���װ���ǣ��γ�һ����ͳһ��ʽ�Ŀɵ��ö��󣩣�
/// ���Ƕ���ĳ�Ա��������ָ���޷�ͳһ����
/// ��Ҫ��std::bind���ʹ�ã�
/// 
/// C++���÷Ǿ�̬�ĳ�Ա����ʱ�����õ���һ��__thiscall�ĺ������÷�ʽ���������ֵ��÷�ʽ���������ڱ����ʱ��
/// ���ڵ��õĺ����βα�������һ��ָ����øó�Ա������ָ�룬Ҳ�������Ǿ���˵��thisָ�롣
/// ����������ĳ�Ա������ʵ���Ǻ���󶨵ģ�ֻ�ǷǾ�̬�����ĵ��÷�ʽ��__thiscall,��Ҫͨ�������������
/// 
/// std::bind���ã����ɵ��ö����������һ��󶨳�һ���º�����
///				  ����Ԫ�ɵ��ö���ת����һԪ���ߣ�n-1��Ԫ����ֻ�󶨲��ֲ�����
///				  �ԷǾ�̬�����Ա��������ָ����а���Ҫָ�����ַ������� &ClassType::FuncName���Ͷ����ַ��&classObj��
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
	/// ��������ݳ�Աָ��,�����Ϊһ���ɵ��ö���ע�ⷵ������Ӧ��Ϊ���ã���ֵ��
	/// </summary>
	/// <returns></returns>
	std::function<int& (void)> data_ptr = std::bind(&Foo::m_i, &foo);
	data_ptr() = 100;
	std::cout << foo.m_i << std::endl; // 100
}