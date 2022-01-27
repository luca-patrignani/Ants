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


int main() {
	for(auto d = FIRST_REGULAR_DIRECTION; d < TOTAL_REGULAR_DIRECTIONS; d = static_cast<direction>((direction) d + 1)) {
		testOppD(d);
	}
	testOppD(NO_MOVE);
	return 0;
}
