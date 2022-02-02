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
	std::list<ant> sub;
	olc::PixelGameEngine* pge{};
	map* m{};

public:
	ant() = default;
	ant(int _x, int _y, olc::PixelGameEngine *_pge, map *_m, const position &_goal);

	/*
	Move the ant "a" according to direction "dir",
	Returns true if the movement is legal, otherwise returns false.
	*/
	bool move(direction dir);

	/* Add a new  subordinate ant stream position x, y
	*/
	void addSub(unsigned _x, unsigned _y);

	/* Search an ant according to its position among ant's subordinate and itself.
	 * Returns the pointer to the ant found, nullptr if not found,
	 */
	ant* searchSub(position _pos, ant* a = nullptr);

	/* Add "n" subordinates to the ant.
	 * Returns none.
	 * */
	void addNSub(unsigned n);

	/* Returns the reference to the first subordinate ant.
	 */
	ant& front() { return sub.front(); }

	/* Draw the ant to the olc::pge screen, if "subToo" the it draws also all its subordinates.
	 * Returns none.
	 */
	void print(bool subToo = true) const;

	/* Move the ant towards the "goal".
	 * Returns true if the ant has actually moved,
	 * else false.
	 */
	bool moveToGoal(bool subToo);

	/*Look into the map to the direction "d"
	 * Returns the land.
	 * */
	land look(direction d) const;
};



ant::ant(int _x, int _y, olc::PixelGameEngine *_pge, map *_m, const position &_goal = NULLPOS) :
	pos(_x, _y), pge(_pge), m(_m) {
	sub = std::list<ant>();
	if(_goal == NULLPOS)
		goal = pos;
	else
		goal = _goal;
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

	if (!m->traversable(x, y)) // if that piece of land is not traversable
		return false;
	else {
		pos.y = y;
		pos.x = x;
		return true;
	}
}

void ant::addSub(unsigned _x, unsigned _y) {
	sub.emplace_back(ant(_x, _y, pge, m));
}

ant *ant::searchSub(position _pos, ant* a) {
	if(a == nullptr)
		a = this;

	// If the ant a is the ant, return it
	if(a->pos == _pos)
		return a;

	// Else search it within its subordinate.
	for(auto& i: a->sub) {
		ant* newAnt = searchSub(_pos, &i);
		if (newAnt != nullptr)
			return newAnt;
	}
	return nullptr;
}

// Dumb moving function
bool ant::moveToGoal(bool subToo) {
	if(subToo)
		for(auto& s: sub)
			s.moveToGoal(true);

	if(pos == goal)
		return true;

	// the vector which connects the current position and the goal
	auto p0_p = goal - pos;


	// Prime solution
	direction movement = vectToDirection(p0_p.x, p0_p.y);
	if(move(movement)) {
		return true;
	}
/*
	// Complementary solution
	auto cd = complementaryDirections(movement);
	direction newMovement;
	do {
		newMovement = cd.next();
		if(!(newMovement % !previous) && move(newMovement)) {
			previous = newMovement;
			return true;
		}
	} while(newMovement != NO_MOVE);

	// Opposite solution
	if(move(!movement)) {
		previous = movement;
		return true;
	}

	// Complementary solution with opposite direction
	{
		auto cd = complementaryDirections(!movement);
		direction newMovement;
		do {
			newMovement = cd.next();
			if (move(newMovement)) {
				previous = newMovement;
				return true;
			}
		} while (newMovement != NO_MOVE);
	}
*/
	// If we can do nothing do not move and return false
	return false;
}

/*
bool ant::moveToGoal() {
	if(pos == goal)
		return true;

	// Move to the goal
	// the vector which connects the current position and the goal
	auto p0_p = goal - pos;
	// Prime solution
	direction movement = vectToDirection(p0_p.x, p0_p.y);
	if(move(movement)) {
		previous = INVALID;
		return true;
	}

	if(previous != INVALID) {
		if(move(previous))
			return true;
		else {
			auto newPrevious = previous;
			do {
				if(rightOrLeft)
					newPrevious = right(newPrevious);
				else
					newPrevious = left(newPrevious);
				if(move(newPrevious))
					return true;
			} while(previous != newPrevious);
		}

	}

	// If an obstacle is encountered, choose a complementary direction e keep it.
	auto cp = complementaryDirections(movement);
	direction newDirection;

	do {
		newDirection = cp.next();
		if(move(newDirection)) {
			previous = newDirection;
			rightOrLeft = cp.isRightOrLeft();
			return true;
		}
	} while(newDirection != NO_MOVE);

	if(move(!movement))
		return true;
	return false;

		// If an obstacle is encountered, turn
}
*/

land ant::look(direction d) const {
	position wereLookingTo = pos + directionToVect(d);
	auto l = m->operator()(wereLookingTo.x, wereLookingTo.y);
	return l;
}

void ant::addNSub(unsigned int n) {
	auto _x = pos.x + 1;
	auto _y = pos.y;
	for(unsigned i = 0; i < n; ++i)
		addSub(_x, _y++);
}

void ant::print(bool subToo) const {
	pge->Draw(pos, olc::BLACK);
	if(subToo)
		for(auto i: sub)
			i.print(true);
}




