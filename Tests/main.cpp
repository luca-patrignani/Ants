//
// Created by Luca on 27/01/2022.
//

#include "../direction.h"
#include "../ant.h"
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

void printAnt(ant a, char t = 1) {
	std::cout << t << a.pos << std::endl;
	for(auto i: a.sub) {
		//std::cout << "\t";
		printAnt(i, '\t');
	}
}



int main() {
	ant a = ant(10, 10, 10, nullptr, nullptr);
	a.addNSub(10);
	a.front().addNSub(5);
	a.front().front().addNSub(4);
	std::cout << a.searchSub({11, 10})->pos;
	return 0;
}
