#pragma once
#include <string>
#include <map>
///////////////// 用using来定义模板别名 ////////////////////////////////////////////
/// using覆盖了typedef的所有功能，建议使用using

typedef unsigned int u_int;
using u_int = unsigned int;

typedef int (*func_int)(int, int);
using func_int = int(*)(int, int);


/// 模板别名，typedef无法直接重定义一个模板，需要外敷模板，而using则不需要

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
