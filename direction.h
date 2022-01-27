//
// Created by Luca on 26/01/2022.
//

#ifndef PROVACLION_DIRECTION_H
#define PROVACLION_DIRECTION_H

#include <stdexcept>
#include <cstdlib>
#include <ctime>

typedef enum {
	UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT,
	TOTAL_REGULAR_DIRECTIONS,
	FIRST_REGULAR_DIRECTION = UP_LEFT,
	LAST_REGULAR_DIRECTION = LEFT,
	NO_MOVE,
	INVALID
} direction;


// Opposite direction
direction operator!(const direction& d) {
	switch (d) {
		case UP_LEFT: return DOWN_RIGHT;
		case UP: return DOWN;
		case UP_RIGHT: return DOWN_LEFT;

		case LEFT: return RIGHT;
		case NO_MOVE: return NO_MOVE;
		case RIGHT: return LEFT;

		case DOWN_LEFT: return UP_RIGHT;
		case DOWN: return UP;
		case DOWN_RIGHT: return UP_LEFT;

		default: throw std::invalid_argument("Invalid direction\n");
	}
}


class complementaryDirections {
private:
	direction _right;
	direction _left;
	bool rightOrLeft; // right -> true, left -> false
	bool firstOrSecond; // first -> true, second -> false
	static const bool FIRST = true, SECOND = false;


	static direction right(const direction d) {
		if(d + 1 < TOTAL_REGULAR_DIRECTIONS)
			return (direction) (d + 1);
		if(d + 1 == TOTAL_REGULAR_DIRECTIONS)
			return FIRST_REGULAR_DIRECTION;
		if(d + 1 > TOTAL_REGULAR_DIRECTIONS)
			throw std::range_error("Non-regular direction\n");
	}

	static direction left(const direction d) {
		if(d > 0)
			return (direction) (d - 1);
		if(d == 0)
			return LAST_REGULAR_DIRECTION;
		if(d < 0)
			throw std::range_error("Non-regular direction\n");
	}

public:
	explicit complementaryDirections(direction origin) {
		if(!(origin >= 0 && origin < TOTAL_REGULAR_DIRECTIONS))
			throw std::range_error("Non-regular direction\n");

		std::srand(time(nullptr));
		_right = right(origin);
		_left = left(origin);
		rightOrLeft = (bool) (std::rand() % 2);
		firstOrSecond = FIRST;
	}

	direction next() {
		if(_left == _right)
			return NO_MOVE;

		if(firstOrSecond) {
			firstOrSecond = SECOND;
			if(rightOrLeft)
				return _right;
			else
				return _left;
		}
		else {
			firstOrSecond = FIRST;
			direction r;
			if(!rightOrLeft)
				r = _right;
			else
				r = _left;

			_right = right(_right);
			_left = left(_left);
			rightOrLeft = (bool) (std::rand() % 2);
			return r;
		}
	}

};

/*
vect directionToVect(const direction d) {
	switch (d) {
		case UP_LEFT: return {-1, -1};
		case UP: return {0, -1};
		case UP_RIGHT: return {1, -1};

		case LEFT: return {-1, 0};
		case NO_MOVE: return {0, 0};
		case RIGHT: return {1, 0};

		case DOWN_LEFT: return {-1, 1};
		case DOWN: return {0, 1};
		case DOWN_RIGHT: return {1, 1};

		default: throw std::invalid_argument("Invalid direction\n");
	}
}
*/

/*direction vectToDirection(const vect v) {
	switch (v) {
		case vect(-1, -1): return UP_LEFT;
		case vect(0, -1): return UP;
		case vect(1, -1): return UP_RIGHT;

		case vect(-1, 0): return LEFT;
		case vect(0, 0): return NO_MOVE;
		case vect(1, 0): return RIGHT;

		case vect(-1, 1): return DOWN_LEFT;
		case vect(0, 1): return DOWN;
		case vect(1, 1): return DOWN_RIGHT;

		default: throw std::invalid_argument("Invalid direction\n");
	}
}*/




#endif //PROVACLION_DIRECTION_H
