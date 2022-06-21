#include <iostream>
#include <thread>
#include <mutex>
#include <string>

#include "Conqu.hpp"

int main() {

	Conqu<int> lst;
	lst.push_back(1);
	lst.push_back(3);
	lst.push_back(5);
	lst.push_front(7);
	lst.push_front(9);
	lst.push_front(11);
	lst.push_back(44);
	lst.push_back(33);

	std::cout << "Size = " << lst.getSize() << "\n\n";

	for (size_t i = 0; i < lst.getSize(); i++) {
		std::cout << lst[i] << "\n";
	}

	lst.pop_front();

	std::cout << "\nSize = " << lst.getSize() << "\n\n";

	for (size_t i = 0; i < lst.getSize(); i++) {
		std::cout << lst[i] << "\n";
	}

	std::cout << "\nFront = " << lst.front() << "\n";
	std::cout << "Back = " << lst.back() << "\n\n";

	lst.pop_back();
	std::cout << "Back = " << lst.back() << "\n";
	std::cout << "Size = " << lst.getSize() << "\n\n";

	for (size_t i = 0; i < lst.getSize(); i++) {
		std::cout << lst[i] << "\n";
	}
	std::cout << "\n";

	return 0;
}