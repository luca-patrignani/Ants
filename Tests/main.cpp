//
// Created by Luca on 27/01/2022.
//

#include "../direction.h"
#include <iostream>

std::string printDirection(const direction d) {

}

void testCD(direction d) {
	std::cout << "Start of " << __FUNCTION__ << " for " << d << std::endl;
	auto cd = complementaryDirections(d);
	auto newD = cd.next();
	while(newD != NO_MOVE) {
		std::cout << newD << std::endl;
		newD = cd.next();
	}
	std::cout << "End of " << __FUNCTION__ << " for " << d << std::endl;
}

void testOppD(direction d) {
	printf("return (d == %d && !d == %d);\n", d, !d);
}

void testOpModulo(direction a, direction b) {
	std::cout << "Start of " << __FUNCTION__ << " for " << a << " and " << b << std::endl;
	std::cout << a % b << std::endl;
	std::cout << "End of " << __FUNCTION__ << " for " << a << " and " << b << std::endl;
}

void testDirToVec(direction d) {
	std::cout << "Start of " << __FUNCTION__ << " for " << d << std::endl;
	std::cout << directionToVect(d) << std::endl;
	std::cout << "End of " << __FUNCTION__ << " for " << d << std::endl;
}

int main() {
	for(auto a = FIRST_REGULAR_DIRECTION; a < TOTAL_REGULAR_DIRECTIONS; a = static_cast<direction>((direction) a + 1)) {
		testDirToVec(a);
	}
	testDirToVec(NO_MOVE);
	return 0;
}
