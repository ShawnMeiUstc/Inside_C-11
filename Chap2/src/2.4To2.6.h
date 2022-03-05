#pragma once
#include <vector>
#include <memory>
#include <xstddef>

/// https://stackoverflow.com/questions/10890653/why-would-i-ever-use-push-back-instead-of-emplace-back
/// The actual difference between these two statements is that the more powerful emplace_back will call any type of constructor out there, 
/// whereas the more cautious push_back will call only constructors that are implicit.
/// Implicit constructors are supposed to be safe
///
void f() {
	std::vector<std::unique_ptr<int>> v;
	int a = 1;
	v.emplace_back(std::addressof(a)); // compiles
	v.push_back(std::addressof(a)); // fails to compile
}

/// std::unique_ptr<T> has an explicit constructor from T *. 
/// Because emplace_back can call explicit constructors, passing a non-owning pointer compiles just fine. 
/// However, when v goes out of scope, 
/// the destructor will attempt to call delete on that pointer, which was not allocated by new because it is just a stack object. 
/// This leads to undefined behavior.