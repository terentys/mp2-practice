#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "../include/Complex.hpp"

int main() {
	Complex c;
	std::cin >> c;
	std::cout << std::fixed << std::setprecision(2) << c << std::endl;

	std::cout << (c + Complex(4.0f, 2.0f)) << std::endl;

	try {
		std::cout << (c / Complex(0.0f, 0.0f)) << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}