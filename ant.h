#pragma once

#include <list>
#include "olcPixelGameEngine.h"
#include "direction.h"
#include "map.h"
#include "olcPixelGameEngine.h"

typedef olc::vi2d position;
const position NULLPOS = position(-1, -1);

class ant {
public:
	position pos;
	position goal;
	unsigned life;
	bool ifCarryFood;
	std::list<ant> sub;
	olc::PixelGameEngine* pge;
	map* m;

public:
	ant() = default;
	/*
	Construct the ant
	*/
	ant(int _x, int _y, unsigned _life, olc::PixelGameEngine* _pge, map* _m);

	/*
	Move the ant "a" according to direction "dir",
	Returns true if the movement is legal, otherwise returns false.
	*/
	bool move(direction dir);

	/* Add a new  subordinate ant stream position x, y
	*/
	void addSub(unsigned _x, unsigned _y, unsigned _life) {
		sub.emplace_back(ant(_x, _y, _life, pge, m));
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

	bool moveToGoal() { // TODO: TESTING
		if(pos == goal)
			return true;

		// the vector which connects the current position and the goal
		auto p0_p = goal - pos;

		// Prime solution
		direction movement = vectToDirection(p0_p.x, p0_p.y);
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

	/*Look into the map to the direction "d"
	 * Returns the land.
	 * */
	 land look(direction d) {
		position wereLookingTo = pos + directionToVect(d);
		auto l = m->operator()(wereLookingTo.x, wereLookingTo.y);
		return l;
	}
};



ant::ant(int _x, int _y, unsigned _life, olc::PixelGameEngine* _pge, map* _m): pos(_x, _y), life(_life), pge(_pge), m(_m) {
	ifCarryFood = false;
	sub = std::list<ant>();
	goal = NULLPOS;
}


bool ant::move(direction dir) {
	int y = pos.y, x = pos.x;
	switch (dir) {
		case UP_LEFT: --y; --x; break;
		case UP: --y; break;
		case UP_RIGHT: --y; ++x; break;

		case LEFT: --x; break;
		case RIGHT: ++x; break;

		case DOWN_LEFT: ++y; --x; break;
		case DOWN: ++y; break;
		case DOWN_RIGHT: ++y; ++x; break;

		default: return false;
	}

	if (!m->crossable(x, y)) // if that piece of land is not crossable
		return false;
	else {
		pos.y = y;
		pos.x = x;
		return true;
	}
}





