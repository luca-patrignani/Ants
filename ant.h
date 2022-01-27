#pragma once

#include <list>
#include "olcPixelGameEngine.h"
#include "direction.h"

typedef olc::vi2d position;
const position NULLPOS = position(-1, -1);

class ant {
public:
	position pos;
	position goal;
	unsigned life;
	bool ifCarryFood;
	bool alreadyMoved; // TODO: We'll see if it is needed
	std::list<ant> sub;
	olc::PixelGameEngine* pge;

public:
	ant() {}
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
/*
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
*/
	bool moveToGoal() {
		if(pos == goal)
			return true;

		// the vector which connects the current position and the goal
		auto p0p = goal - pos;

		// Prime solution
		direction movement = vectToDirection(p0p.x, p0p.y);
		if(move(movement))
			return true;

		// Complementary solution
		auto cd = complementaryDirections(movement);
		direction newMovement;
		do {
			newMovement = cd.next();
			if(move(newMovement))
				return true;
		} while(newMovement != NO_MOVE);

		// Opposite solution
		if(move(!movement))
			return true;

		// If we can do nothing do not move and return false
		return false;
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





