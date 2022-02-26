#include "1.4.h"
#include <iostream>


int main() {
	for (auto i : Range::range(1.1, 10.1, 0)) {
		std::cout << i << " ";
	}
}