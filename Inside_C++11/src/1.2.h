#pragma once
#include <string>
#include <map>
///////////////// ��using������ģ����� ////////////////////////////////////////////
/// using������typedef�����й��ܣ�����ʹ��using

typedef unsigned int u_int;
using u_int = unsigned int;

typedef int (*func_int)(int, int);
using func_int = int(*)(int, int);


/// ģ�������typedef�޷�ֱ���ض���һ��ģ�壬��Ҫ���ģ�壬��using����Ҫ

template<typename Val>
struct str_map0 {
	typedef std::map <std::string, Val> type;
};

str_map0<int>::type str_int_map0;
str_map0<std::string>::type str_str_map0;


template<typename Val>
using str_map1 = std::map<std::string, Val>;

str_map1<int> str_int_map1;
str_map1<std::string> str_str_map1;

///////////////////////////////////////////////////

template<typename T>
struct func_t0 {
	typedef void(*type)(T, T);
};

func_t0<int>::type f0;



template<typename T>
using func_t1 = void(*)(T, T);

func_t1<int> f1;
