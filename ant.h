#pragma once

#include <list>
#include "olcPixelGameEngine.h"

typedef olc::vi2d vect;
typedef olc::vi2d position;
const position NULLPOS = position(-1, -1);

typedef enum {
	DUMMY = 0,

	UP_LEFT,             UP,                UP_RIGHT,
	   LEFT,             NO_MOVE=0,            RIGHT=-LEFT,
  DOWN_LEFT=-UP_RIGHT,   DOWN = -UP,      DOWN_RIGHT=-UP_LEFT,

  TOTAL_DIRECTIONS
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

std::vector<direction> complementary(const direction& d) {
	switch (d) {
		
	}
}




class ant {
public:
	position pos;

	unsigned life;
	bool ifCarryFood;
	bool alreadyMoved; // TODO: We'll see if it is needed
	std::list<ant> sub;
	olc::PixelGameEngine* pge;

public:
	position goal;
	/*
	Construct the ant
	*/
	ant(int _x, int _y, unsigned _life, olc::PixelGameEngine* _pge);

	/*
	Move the ant "a" according to direction "dir",
	Returns true if the movement is legal, otherwise returns false.
	*/
	bool move(direction dir);

	/* Add a new  subordinate ant in position x, y
	*/
	void addSub(unsigned _x, unsigned _y, unsigned _life) {
		sub.emplace_back(ant(_x, _y, _life, pge));
	}

	/* Search an ant according to its position among ant's subordinate and itself.
	 * Returns the pointer to the ant found, nullptr if not found,
	 */
	ant* searchSub(position _pos, ant* a = nullptr) {
		if(a == nullptr)
			a = this;

		// If the ant a is the ant, return it
		if(pos == _pos)
			return a;

		// Else search it within its subordinate.
		for(auto& i: a->sub) {
			ant* newAnt = searchSub(_pos, &i);
			if (newAnt != nullptr)
				return newAnt;
		}
		return nullptr;
	}

	void addNSub(unsigned n) {
		auto _x = pos.x + 1;
		auto _y = pos.y;
		for(unsigned i = 0; i < n; ++i)
			addSub(_x, _y++, life);
	}

	ant& front() {
		return sub.front();
	}

	void print(bool subToo = true) {
		pge->Draw(pos, olc::BLACK);
		if(subToo)
			for(auto i: sub)
				i.print(true);
	}

	void setGoal(const position& _goal) { goal = _goal; }

	void moveToGoal() {
		int x = pos.x, y = pos.y;
		int gx = goal.x, gy = goal.y;
		direction d;
		if(x < gx) {
			if(y < gy)
				d = DOWN_RIGHT;
			else
				if(y == gy)
					d = RIGHT;
				else
					d = UP_RIGHT;
		}
		else if(x == gx) {
			if(y < gy)
				d = DOWN;
			else
			if(y == gy)
				d = NO_MOVE;
			else
				d = UP;
		}
		else {
			if(y < gy)
				d = DOWN_LEFT;
			else
			if(y == gy)
				d = LEFT;
			else
				d = UP_LEFT;
		}

		//if(move(d))

	}

};



ant::ant(int _x, int _y, unsigned _life, olc::PixelGameEngine* _pge): pos(_x, _y), life(_life), pge(_pge) {
	alreadyMoved = false;
	ifCarryFood = false;
	sub = std::list<ant>();
	goal = NULLPOS;
}


bool ant::move(direction dir) {
	int _y = (int)pos.y, _x = (int)pos.x;
	switch (dir) {
		case UP_LEFT: --_y; --_x; break;
		case UP: --_y; break;
		case UP_RIGHT: --_y; ++_x; break;

		case LEFT: --_x; break;
		case RIGHT: ++_x; break;

		case DOWN_LEFT: ++_y; --_x; break;
		case DOWN: ++_y; break;
		case DOWN_RIGHT: ++_y; ++_x; break;

		default: return false;
	}

	if (_y < 0 || _x < 0) // TODO: More checks are needed
		return false;
	else {
		pos.y = _y;
		pos.x = _x;
		return true;
	}
}





